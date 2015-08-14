#include <stdio.h>
#include <stdint.h>

// domain = 0..PI/2, range = 0..+32767
//   JSON.stringify(Array.apply(null, Array(65)).map(function(x, i){return parseInt(Math.sin(i / 64 * Math.PI / 2) * 32767)}))
signed short const kSinLUT[65] =
{
	0,804,1607,2410,3211,4011,4807,5601,
	6392,7179,7961,8739,9511,10278,11038,11792,
	12539,13278,14009,14732,15446,16150,16845,17530,
	18204,18867,19519,20159,20787,21402,22004,22594,
	23169,23731,24278,24811,25329,25831,26318,26789,
	27244,27683,28105,28510,28897,29268,29621,29955,
	30272,30571,30851,31113,31356,31580,31785,31970,
	32137,32284,32412,32520,32609,32678,32727,32757,
	32767
};

signed short	ksin(unsigned int v)
{
	v &= 0xFF;
	signed short s = (v & 0x40)? kSinLUT[64 - (v & 0x3F)] : kSinLUT[(v & 0x3F)];
	return((v & 0x80)? -s : s);
}


enum
{
	Command_None =				0,
	Command_FrameCountBegin =	1,
	Command_Sync =				2,
	Command_IdentifyEndpoint =	3,
	Command_SetAttenuation =	4,
	Command_SetLowPassCorner =	5,
	Command_SetHighPassCorner =	6,
	Command_SetVisualEffects =	7,
};




// Begin G.711 mu-law decoder implementation:

inline unsigned int ReadBigEndian32(unsigned char const* p) {return((p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3]);}

// implemented as tiny individual functions because this is the fastest-running/smallest code-size
//   approach for ARM thumb2. Could also use a single function body with computed goto (gcc only)
int ULawDecode0(int subValue) {return(-31616 + (subValue << 10));}
int ULawDecode1(int subValue) {return(-15744 + (subValue << 9));}
int ULawDecode2(int subValue) {return(-7804 + (subValue << 8));}
int ULawDecode3(int subValue) {return(-3836 + (subValue << 7));}
int ULawDecode4(int subValue) {return(-1852 + (subValue << 6));}
int ULawDecode5(int subValue) {return(-860 + (subValue << 5));}
int ULawDecode6(int subValue) {return(-364 + (subValue << 4));}
int ULawDecode7(int subValue) {return(-116 + (subValue << 3));}
int ULawDecode8(int subValue) {return(31608 - (subValue << 10));}
int ULawDecode9(int subValue) {return(15736 - (subValue << 9));}
int ULawDecodeA(int subValue) {return(7800 - (subValue << 8));}
int ULawDecodeB(int subValue) {return(3832 - (subValue << 7));}
int ULawDecodeC(int subValue) {return(1848 - (subValue << 6));}
int ULawDecodeD(int subValue) {return(856 - (subValue << 5));}
int ULawDecodeE(int subValue) {return(360 - (subValue << 4));}
int ULawDecodeF(int subValue) {return(112 - (subValue << 3));}

typedef int (*ULawDecodeFn)(int subValue);

ULawDecodeFn static ULawDecoder[16] =
{
	&ULawDecode0, &ULawDecode1, &ULawDecode2, &ULawDecode3, &ULawDecode4, &ULawDecode5, &ULawDecode6, &ULawDecode7,
	&ULawDecode8, &ULawDecode9, &ULawDecodeA, &ULawDecodeB, &ULawDecodeC, &ULawDecodeD, &ULawDecodeE, &ULawDecodeF
};



void uLawDecompress(unsigned short* sampleOutput, unsigned char* data, int length)
{
	// decode G.711 u-Law
	for(int i = 0; i < length; i++)
	{
		int b = *data++;
		*sampleOutput++ = ULawDecoder[b >> 4](b & 0x0F);
	}
}



// 0 8480 + x << 10		1000000000000000
// 1 c27f + x << 9		1100000000000000
// 2 e184 + x << 8		1110000000000000
// 3 f104 + x << 7		1111000000000000
// 4 f8c4 + x << 6		1111100000000000
// 5 fca4 + x << 5		1111110000000000
// 6 fe94 + x << 4		1111111000000000
// 7 ff8c + x << 3		1111111110000000

// 8 7b78 - x << 10		0111110000000000 1
// 9 3d78 - x << 9		0011110000000000 2
// A 1e78 - x << 8		0001111000000000 3
// B 0ef8 - x << 7		0000111000000000 4
// C 0738 - x << 6		0000011100000000 5
// D 0358 - x << 5		0000001100000000 6
// E 0168 - x << 4		0000000100000000 7
// F 0070 - x << 3		0000000001110000 9


// -31616	10	<= 3
// -15744	9	<= 2
// -7804	8	<= 3
// -3836	7	<= 1
// -1852	6	<= 3
// -860		5	<= 2
// -364		4	<= 3
// -116		3	*

unsigned char uLawCompress(signed short sample)
{
	// encode G.711 u-Law
	if(sample > 31608)	sample = 31608;
	if(sample < -31616)	sample = -31616;

	if(sample >= 0)
	{
		if(sample > 1848)
		{
			if(sample > 7800)
			{
				if(sample > 15736)	return(0x80 + ((31608 - sample) >> 10));
				else				return(0x90 + ((15736 - sample) >> 9));
			}
			else
			{
				if(sample > 3832)	return(0xA0 + ((7800 - sample) >> 8));
				else				return(0xB0 + ((3832 - sample) >> 7));
			}
		}
		else
		{
			if(sample > 360)
			{
				if(sample > 856)	return(0xC0 + ((1848 - sample) >> 6));
				else				return(0xD0 + ((856 - sample) >> 5));
			}
			else
			{
				if(sample > 112)	return(0xE0 + ((360 - sample) >> 4));
				else				return(0xF0 + ((112 - sample) >> 3));
			}
		}
	}
	else
	{
		if(sample < -1852)
		{
			if(sample < -7804)
			{
				if(sample < -15744)		return(0x00 + ((-(-31616 - sample)) >> 10));
				else					return(0x10 + ((-(-15744 - sample)) >> 9));
			}
			else
			{
				if(sample < -3836)		return(0x20 + ((-(-7804 - sample)) >> 8));
				else					return(0x30 + ((-(-3836 - sample)) >> 7));
			}
		}
		else
		{
			if(sample < -364)
			{
				if(sample < -860)		return(0x40 + ((-(-1852 - sample)) >> 6));
				else					return(0x50 + ((-(-860 - sample)) >> 5));
			}
			else
			{
				if(sample < -116)		return(0x60 + ((-(-364 - sample)) >> 4));
				else					return(0x70 + ((-(-116 - sample)) >> 3));
			}
		}
	}
}


static FILE* gOutputFile;
static FILE* gInputFile;

void UARTWriteBlocking(unsigned char v)
{
	//printf("%i ", v);
	fwrite(&v, 1, 1, gOutputFile);
}

void UARTWriteHeaderSim(int numSamples, int sampleRate, int numChannels)
{
	unsigned int lengthBytes = numSamples * sizeof(unsigned short);
	fwrite("RIFF", 1, 4, gOutputFile);
	unsigned int l = 36 + lengthBytes;
	fwrite(&l, 1, sizeof(unsigned int), gOutputFile);
	fwrite("WAVE" "fmt " "\x10\0\0\0" "\x01\0" "\x02\0", 1, 16, gOutputFile);
	fwrite(&sampleRate, 1, sizeof(unsigned int), gOutputFile);
	sampleRate *= numChannels;
	fwrite(&sampleRate, 1, sizeof(unsigned int), gOutputFile);
	fwrite("\x02\0\x10\0" "data", 1, 8, gOutputFile);
	fwrite(&lengthBytes, 1, sizeof(unsigned int), gOutputFile);
}

unsigned char UARTChar(void)
{
	return(fgetc(gInputFile));
}

int AudioFIFOIsFull(void)
{
	return(0);
}

void AudioFIFOWrite(int sampleL, int sampleR)
{
	if(sampleL < -32768) sampleL = -32768;
	if(sampleL > 32767) sampleL = 32767;

	if(sampleR < -32768) sampleR = -32768;
	if(sampleR > 32767) sampleR = 32767;

	unsigned char d[4] = {sampleL, sampleL >> 8, sampleR, sampleR >> 8};
	fwrite(d, 1, 4, gOutputFile);
}


inline int64_t	mul(int32_t stage, int32_t coeff)
{
	return(((int64_t)stage * coeff) >> 15);
}

int main(int numArgs, char const* const* args)
{
	if(1)
	{
		int errors = 0;
		for(int i = -32768; i < 32767; i++)
		{
			unsigned char v = uLawCompress(i);
			int vd = ULawDecoder[v >> 4](v & 0x0F);

			float rerr = ((float)vd) / ((float)i) - 1.f, oerr = ((float)vd) - ((float)i);

			if(rerr < 0.f) rerr = -rerr;
			if(oerr < 0.f) oerr = -oerr;

			if((rerr > 0.067f) && (oerr > 64.f))
			{
				printf("error %i => 0x%02x => %i error %.1f%%, offset %.0f.\n", i, v, vd, rerr * 100.f, oerr);
				errors++;
			}

			unsigned char check = uLawCompress(vd);
			int vdd = ULawDecoder[check >> 4](check & 0x0F);
			if(vd != vdd)
			{
				printf("round-trip error: %i => 0x%02x => %i\n", vd, check, vdd);
				errors++;
			}
		}
	}

	if(numArgs == 1)
	{
		if((gOutputFile = fopen("stream.bin", "wb")) == 0)
		{
			printf("error, could not open output file ./stream.bin for writing.\n");
			return(1);
		}

		int wlf = (1 << 12), whf = (77 << 16), thlf = 0, thhf = 0, count = 0;

		for(int t = 0; t < 320000; t++)
		{
			int lf = ksin(thlf >> 16), hf = ksin(thhf >> 16);
			
			if(count == 0)
			{
				UARTWriteBlocking(0x7F);
				UARTWriteBlocking(0xE0);
				UARTWriteBlocking(Command_FrameCountBegin);
				UARTWriteBlocking(160);
			}
			
			//UARTWriteBlocking(lf);
			//UARTWriteBlocking(lf >> 8);
			UARTWriteBlocking(uLawCompress(lf));
			
			thlf += wlf;
			//thhf += whf;

			if((wlf += (1 + (wlf >> 14))) > (83 << 16))
				wlf = (1 << 12);
			
			/*if((whf += (whf >> 16)) > (83 << 16))
				whf = (20 << 16);
			*/

			if(++count == 320)
			{
				count = 0;	// this triggers a re-sync
			}
		}
		fclose(gOutputFile);
		return(0);
	}
	else
	{
		if((gOutputFile = fopen("stream.wav", "wb")) == 0)
		{
			printf("error, could not open output file ./stream.wav for writing.\n");
			return(1);
		}

		if((gInputFile = fopen(args[1], "rb")) == 0)
		{
			printf("error, could not open input file %s for reading.\n", args[1]);
			return(1);
		}

		enum StreamState
		{
			StreamState_Uninitialized,
			StreamState_ReceivedInit0,
			StreamState_CommandPhase,
			StreamState_CommandValuePhase,
			StreamState_FrameCountBegin,
			StreamState_Active,
		};

		unsigned int	frameCount = 0,
						state = StreamState_Uninitialized,
						command = Command_None,
						lpc = 7500, hpc = 4000,
						identify = 0,
						attenuation = 29000,
						vfx = 0;
		signed int		in[2] = {0}, lp[2] = {0}, hp[2] = {0};

		UARTWriteHeaderSim(320000, 32000, 2);

		while(!feof(gInputFile))
		{
			// process next received character
			switch(state)
			{
			case StreamState_Uninitialized:
				if(UARTChar() == 0x7F)
					state = StreamState_ReceivedInit0;
				break;

			case StreamState_ReceivedInit0:
				if(UARTChar() == 0xE0)	state = StreamState_CommandPhase;
				else					state = StreamState_Uninitialized;
				break;

			case StreamState_CommandPhase:
				switch((command = UARTChar()))
				{
				case Command_FrameCountBegin:
					state = StreamState_FrameCountBegin;
					break;
				case Command_Sync:
					break;
				case Command_IdentifyEndpoint:
				case Command_SetAttenuation:
				case Command_SetLowPassCorner:
				case Command_SetHighPassCorner:
				case Command_SetVisualEffects:
					state = StreamState_CommandValuePhase;
					break;
				default:
					state = StreamState_Uninitialized;	// error and desynchronize
					break;
				}
				break;

			case StreamState_CommandValuePhase:
				{
					int value = UARTChar();
					switch(command)
					{
					case Command_IdentifyEndpoint:
						identify = value;
						break;
					case Command_SetAttenuation:
						attenuation = value;
						break;
					case Command_SetLowPassCorner:
						lpc = value << 8;
						break;
					case Command_SetHighPassCorner:
						hpc = value << 8;
						break;
					case Command_SetVisualEffects:
						vfx = !!value;
						break;
					}
				}
				state = StreamState_CommandPhase;
				break;

			case StreamState_FrameCountBegin:
				frameCount = (UARTChar() << 1);
				state = StreamState_Active;
				break;

			case StreamState_Active:
				{
					unsigned char d = UARTChar();

					in[1] = in[0];
					in[0] = ULawDecoder[d >> 4](d & 0x0F) << 16;
					
					lp[1] = lp[0];
					lp[0] = (signed int)(mul(in[0], lpc) + mul(lp[1], 32768 - lpc));

					hp[1] = hp[0];
					hp[0] = (signed int)(mul(in[0], (65536 - hpc) >> 1) + mul(in[1], (-65536 + hpc) >> 1) + mul(hp[1], 32768 - hpc));

					(void)vfx;
					(void)identify;

					while(AudioFIFOIsFull())
						;	// should be a minimally-wasteful synchronization

					AudioFIFOWrite(mul(lp[0], attenuation) >> 16, mul(hp[0], attenuation) >> 16);
					
					if(--frameCount == 0)
						state = StreamState_Uninitialized;
				}
				break;
			}
		}
		//printf("done\n");

		fclose(gInputFile);
		fclose(gOutputFile);
	}
}
