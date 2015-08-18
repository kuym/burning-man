#include <GalagoAPI.h>
#include <LPC13xx.h>
#include <stdint.h>
#include "audio-common.h"


using namespace Galago;

unsigned int	System_divideClockFrequencyRounded(unsigned int n, unsigned int d);

unsigned int const	kAudioBufferLength = 1200;
volatile signed short		gAudioBuffer[kAudioBufferLength];
volatile unsigned int		gAudioTail, gAudioFill;

unsigned int const	kUARTBufferLength = 100;
volatile unsigned char		gUARTBuffer[kUARTBufferLength];
volatile unsigned int		gUARTTail, gUARTFill;


extern "C" 	void		IRQ_Timer1(void)
{
	// hardware has already toggled the BCK signal, so output the next sample of left-justified audio data right away
	*LPC1300::Timer1Interrupts = LPC1300::TimerInterrupts_Match0Flag;
	
	if((gAudioFill > 0) && ((!!(*LPC1300::Timer1ExternalMatch & LPC1300::TimerExternalMatch_Match0State)) == (gAudioTail & 1)))
	{
		*LPC1300::SPI0Data = ((unsigned short const*)gAudioBuffer)[gAudioTail++];
		gAudioFill--;
		if(gAudioTail >= kAudioBufferLength)
			gAudioTail = 0;
	}
	else
		*LPC1300::SPI0Data = 0;
}

void		AudioDACStart(int sampleRate)
{
	InterruptsDisable();
	// shutdown
	*LPC1300::Timer1Control = LPC1300::TimerControl_Reset;
	*LPC1300::Timer1MatchControl = 0;
	*LPC1300::ClockControl &= ~LPC1300::ClockControl_Timer1;
	
	if(sampleRate != 0)
	{
		io.p5.setOutput();
		io.p5 = true;
		io.p5.setPWM();			// monotonic sample clock (aka left-right clock, word select)
		
		// set up PWM on p5 (timer1 match0) and interrupt for audio samples
		*LPC1300::ClockControl |= LPC1300::ClockControl_Timer1;
		
		*LPC1300::Timer1Control = (LPC1300::TimerControl_Enable | LPC1300::TimerControl_Reset);
		
		*LPC1300::Timer1Prescaler = System_divideClockFrequencyRounded(system.getMainClockFrequency(), sampleRate * 4);
		*LPC1300::Timer1MatchControl =	LPC1300::TimerMatchControl_Match0Interrupt
										| LPC1300::TimerMatchControl_Match0Reset;
		*LPC1300::Timer1ExternalMatch = LPC1300::TimerExternalMatch_Match0Toggle;
		*LPC1300::Timer1Match0 = 1;
		
		*LPC1300::Timer1Control = LPC1300::TimerControl_Enable;
		
		*LPC1300::InterruptEnableSet1 = LPC1300::Interrupt1_Timer1;
	}
	InterruptsEnable();
}

void		AudioFIFOInit(void)
{
	gAudioTail = 0;
	gAudioFill = 0;
}

bool		AudioFIFOIsFull(void)
{
	InterruptsDisable();

	int full = (gAudioFill >= kAudioBufferLength);

	InterruptsEnable();

	return(full);
}

void		AudioFIFOWrite(signed short sampleLeft, signed short sampleRight)
{
	InterruptsDisable();
	unsigned int tail = gAudioTail, fill = gAudioFill;

	if(fill >= kAudioBufferLength)
	{
		gAudioTail = tail = (tail < (kAudioBufferLength - 1))? (tail + 2) : 0;
		fill -= 2;
	}

	unsigned int h = ((tail + fill) >= kAudioBufferLength)?
			(tail + fill - kAudioBufferLength)
		:	(tail + fill);

	gAudioBuffer[h] = sampleLeft;
	gAudioBuffer[h + 1] = sampleRight;
	gAudioFill = fill + 2;
	InterruptsEnable();
}

// force the distance between the head and tail of the circular buffer to be 'newOffset' by
//   dropping the oldest samples.  Be aware that this operates in stereo sample pairs.
void		AudioFIFOSynchronize(unsigned int newOffset)
{
	newOffset <<= 1;	// act on stereo pairs

	InterruptsDisable();

	unsigned int head = gAudioTail + gAudioFill;
	if(head > kAudioBufferLength)
		head -= kAudioBufferLength;

	gAudioTail = (newOffset < head)? (head + kAudioBufferLength - newOffset) : (head - newOffset);
	gAudioFill = newOffset;

	InterruptsEnable();
}

void		SPIStart(unsigned int bitRate)
{
	*LPC1300::PeripheralnReset &= ~LPC1300::PeripheralnReset_SPI0;	// assert reset
	
	if(bitRate > 0)
	{
		*LPC1300::ClockControl |= LPC1300::ClockControl_SPI0;	// enable SPI0 clock

		*LPC1300::SPI0ClockDivider = 1;
		
		*LPC1300::PeripheralnReset |= LPC1300::PeripheralnReset_SPI0;	// deassert reset
		
		// This finds three prescalers, A, B and C such that (Fcpu / (A + 1) / B / C) = bitRate, where C is an even number 2 to 254.
		//   so as to avoid factoring, we cheat here by extracting an 8-bit mantissa (A) and computing 2^exponent, expressed in B and C
		
		unsigned int divisor = (system.getCoreFrequency() / bitRate) >> 1;
		unsigned int magnitude = 32 - __builtin_clz(divisor);
		unsigned int scale = 0, prescale = 2;
		
		if(magnitude > 8)
		{
			if(magnitude > 16)
			{
				prescale = 1 << (magnitude - 15);
				magnitude = 16;
			}
			divisor >>= (magnitude - 8); // set mantissa
			
			scale = ((1 << (magnitude - 8)) - 1);
		}
		else
			scale = 0;
		
		*LPC1300::SPI0Control0 = (scale << 8) | LPC1300::SPI0Control0_16BitTransfer;	// 16 bits per symbol
		*LPC1300::SPI0Control1 = LPC1300::SPI0Control1_Enable;
		*LPC1300::SPI0ClockPrescaler = prescale;
		*LPC1300::SPI0ClockDivider = divisor - 1;
		
		io.sck.setMode(IO::Pin::SPI);
		io.miso.setMode(IO::Pin::SPI);
		io.mosi.setMode(IO::Pin::SPI);
	}
	else
	{
		*LPC1300::ClockControl &= ~LPC1300::ClockControl_SPI0;	// disable SPI0 clock
		
		// set pin modes back
		io.sck.setMode(IO::Pin::Default);
		io.miso.setMode(IO::Pin::Default);
		io.mosi.setMode(IO::Pin::Default);
	}
}

void			UARTInit(void)
{
	gUARTTail = 0;
	gUARTFill = 0;
}

bool			UARTCharAvailable(void)
{
	InterruptsDisable();
	bool isAvailable = (gUARTFill > 0);
	InterruptsEnable();
	return(isAvailable);
}

unsigned char	UARTChar(void)
{
	InterruptsDisable();
	unsigned char c = gUARTBuffer[gUARTTail];
	gUARTFill--;
	if(++gUARTTail == kUARTBufferLength)
		gUARTTail = 0;
	InterruptsEnable();
	return(c);
}

bool			UARTCanWrite(void)
{
	return(*LPC1300::UARTLineStatus & LPC1300::UARTLineStatus_TxHoldingRegisterEmpty);
}
void			UARTWrite(unsigned char value)
{
	*LPC1300::UARTData = value;
}

void			UARTWriteBlocking(unsigned char value)
{
	while(!UARTCanWrite())
		;
	*LPC1300::UARTData = value;
}

static void		UARTInterrupt(void)
{
	unsigned int iid;
	while(((iid = *LPC1300::UARTInterruptID) & LPC1300::UARTInterruptID_InterruptPending) == 0)
	{
		switch(iid & LPC1300::UARTInterruptID_ReasonMask)
		{
		case LPC1300::UARTInterruptID_ReceiveException:
			*LPC1300::UARTScratch = *LPC1300::UARTLineStatus;
			break;
			
		case LPC1300::UARTInterruptID_DataAvailable:
		case LPC1300::UARTInterruptID_ReceiveTimeout:
			//receive any available bytes
			while(*LPC1300::UARTLineStatus & LPC1300::UARTLineStatus_ReceiverDataReady)
			{
				if(gUARTFill == kUARTBufferLength)
				{
					gUARTFill--;
					gUARTTail = ((gUARTTail + 1) < kUARTBufferLength)? (gUARTTail + 1) : 0;
				}

				unsigned int h = gUARTTail + gUARTFill;
				if(h > kUARTBufferLength)
					h -= kUARTBufferLength;
				gUARTBuffer[h] = *LPC1300::UARTData;
				gUARTFill++;
			}
			break;
		}
	}
}

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


inline int64_t	mul(int32_t stage, int32_t coeff)
{
	return(((int64_t)stage * coeff) >> 15);
}


int main(void)
{
	// we will use:
	//   - timer1 as a 96KHz timebase, highest interrupt priority
	//   - systick as second-highest interrupt priority
	//   - the UART asynchronously, third-highest interrupt priority
	//   - the SPI asynchronously (via FIFO) but without interrupts

	IO::Pin ampOn, TXnRX;

	ampOn.bind(io.p6);
	ampOn.setOutput();
	TXnRX.bind(io.rts);
	TXnRX.setOutput();

	TXnRX = false;	// initially start in RX mode
	
	ampOn = true;

	system.setCoreFrequency(72000000UL);

	// system.setClockOutputFrequency(72000000UL);
	// io.p1.setMode(IO::Pin::ClockOutput);
	
	AudioFIFOInit();
	UARTInit();

	io.txd.setMode(IO::Pin::UART);
	io.rxd.setMode(IO::Pin::UART);
	
	// now 12, resulting in 375kbps
	system.overrideInterrupt(System::UART, &UARTInterrupt);
	io.serial.startWithExplicitRatio(12, 0, 1, IO::UART::Default);

	// at 2 * 16-bit * 32KHz = 1024KHz. 2MHz gives us headroom and is a clean division of 72MHz
	SPIStart(2000000UL);
	//io.mosi.setOutput();
	
	AudioFIFOInit();
	
	// 32KHz samplerate, stereo, 16-bit
	AudioDACStart(32000);

	(void)ULawDecoder;	// suppress warning
	
	int wlf = (1 << 4), whf = (20 << 16), thlf = 0, thhf = 0, vol = 0, voldir = 1;
	while(1)
	{
		if(!AudioFIFOIsFull())
		{
			int lf = ksin(thlf >> 16), hf = ksin(thhf >> 16);

			(void)hf;
			AudioFIFOWrite(mul(hf, vol) >> 1, mul(lf, vol) >> 1);
			
			thlf += wlf;
			thhf += whf;

			if((wlf += (1 + (wlf >> 16))) > (20 << 16))
				wlf = (1 << 4);
			
			if((whf += (1 + (whf >> 16))) > (60 << 16))
				whf = (20 << 16);

			vol += voldir;
			if((voldir > 0) && (vol >= 65535))
			{
				voldir = -voldir;
				vol = 65535;
			}
			if((voldir < 0) && (vol <= 0))
			{
				voldir = -voldir;
				vol = 0;
			}
		}
	}
}
