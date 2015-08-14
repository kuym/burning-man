#include <GalagoAPI.h>
#include <AudioBlock.h>
#include <LPC13xx.h>

using namespace Galago;

unsigned int	System_divideClockFrequencyRounded(unsigned int n, unsigned int d);

unsigned int const	kAudioBufferLength = 1200;
volatile signed short		gAudioBuffer[kAudioBufferLength];
volatile unsigned int		gAudioTail, gAudioFill;

unsigned int const	kUARTBufferLength = 100;
volatile unsigned char		gUARTBuffer[kUARTBufferLength];
volatile unsigned int		gUARTTail, gUARTFill;


signed short	ksin(unsigned int v);

unsigned int	gT;
signed int		gL, gR, gLD, gRD;

extern "C" 	void		IRQ_Timer1(void)
{
	// hardware has already toggled the BCK signal, so output the next sample of left-justified audio data right away
	*LPC1300::Timer1Interrupts = LPC1300::TimerInterrupts_Match0Flag;
	
	/*
	if(gT++ & 1)
	{
		*LPC1300::SPI0Data = (unsigned short)(gR >> 16);	//ksin(gR >> 3) >> 3;
		gR += gRD;
		if(gR >= (3276 << 16))
		{
			//gR = 3276;
			gRD = -(gRD + (gRD >> 16));
			if(gRD < (-6000 << 16))
				gRD = (-2631 << 16);
		}
		else if(gR <= (-3276 << 16))
		{
			//gR = -3276;
			gRD = -(gRD + (gRD >> 16));
			if(gRD > (6000 << 16))
				gRD = (2631 << 16);
		}
	}
	else
	{
		*LPC1300::SPI0Data = (unsigned short)(gL >> 16);	//ksin(gL >> 3) >> 3;
		gL += gLD;
		if(gL >= (3276 << 16))
		{
			//gL = 3276;
			gLD = -gLD;
		}
		else if(gL <= (-3276 << 16))
		{
			//gL = -3276;
			gLD = -gLD;
		}
	}
	*/

	//io.mosi = !io.mosi;
	
	/*int bits = 16, sample = gT << 10;
	while(bits--)
	{
		LPC1300::GPIO0[1 << 2] = 0;
		__asm__ volatile ("nop"::);
		LPC1300::GPIO1[1 << 8] = (sample & 0x8000)? (1 << 8) : 0;
		sample <<= 1;
		LPC1300::GPIO0[1 << 2] = (1 << 2);
	}
	__asm__ volatile ("nop"::);
	LPC1300::GPIO0[1 << 2] = 0;
	*/

	if((gAudioFill > 0))// && ((!!(*LPC1300::Timer1ExternalMatch & LPC1300::TimerExternalMatch_Match0State)) == (gAudioTail & 1)))
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
		//io.p2.setOutput();	//serial data (SIN)
		//io.p3.setOutput();	//serial clock (BCK)
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

extern "C" void IRQ_UART(void)
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


int main(void)
{
	/*
	gT = 0;
	gL = 0, gR = 0, gLD = 68 << 16, gRD = 2631 << 16;
	*/

	// we will use:
	//   - timer1 as a 96KHz timebase, highest interrupt priority
	//   - systick as second-highest interrupt priority
	//   - the UART asynchronously, third-highest interrupt priority
	//   - the SPI asynchronously (via FIFO) but without interrupts

	IO::Pin mute, ampOn, TXnRX, slaveNMaster;

	mute.bind(io.p4);
	ampOn.bind(io.p1);
	TXnRX.bind(io.rts);
	slaveNMaster.bind(io.p2);

	slaveNMaster.setInput();

	TXnRX = false;	// initially start in RX mode
	
	// mute audio
	mute = true;
	ampOn = false;

	system.setCoreFrequency(72000000UL);
	
	AudioFIFOInit();
	UARTInit();

	// set Timer1 to the highest priority
	//*LPC1300::InterruptPriority10 = (*LPC1300::InterruptPriority10 & ~(0x7 << 21)) | (0 << 21);
	
	// set UART to a lower priority
	//*LPC1300::InterruptPriority11 = (*LPC1300::InterruptPriority11 & ~(0x7 << 21)) | (1 << 21);

	io.txd.setMode(IO::Pin::UART);
	io.rxd.setMode(IO::Pin::UART);
	
	// 1.125Mbps
	io.serial.startWithExplicitRatio(4, 0, 1, IO::UART::Default);

	if(1)
	{
		// at 2 * 16-bit * 48KHz = 1536KHz. 1600KHz gives us headroom and is a clean division of 72MHz
		SPIStart(2000000UL);
		//io.mosi.setOutput();
		
		// 48KHz samplerate, stereo, 16-bit
		AudioDACStart(32000);
		
		while(1)
		{
			int wlf = (1 << 16), whf = (77 << 16), thlf = 0, thhf = 0;
			if(!AudioFIFOIsFull())
			{
				int lf = ksin(thlf >> 16), hf = ksin(thhf >> 16);
				
				AudioFIFOWrite(lf, hf);
				
				thlf += wlf;
				thhf += whf;

				if((wlf += (wlf >> 16)) > (20 << 16))
					wlf = (1 << 16);
				
				if((whf += (whf >> 16)) > (83 << 16))
					whf = (20 << 16);
			}
		}
	}

	int receiverRole = (bool)slaveNMaster;

	if(receiverRole)
	{
		// at 2 * 16-bit * 48KHz = 1536KHz. 1600KHz gives us headroom and is a clean division of 72MHz
		SPIStart(2000000UL);
		//io.mosi.setOutput();
		
		AudioFIFOInit();
		
		// 48KHz samplerate, stereo, 16-bit
		AudioDACStart(32000);
		
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
						expectedCount = 0,
						state = StreamState_Uninitialized,
						command = Command_None,
						lpc = 0, hpc = 0,
						identify = 0,
						attenuation = 0,
						vfx = 0;
		
		while(1)
		{
			while(UARTCharAvailable())
			{
				// process next received character
				switch(state)
				{
				case StreamState_Uninitialized:
					if(UARTChar() == 0x7F)
						state = StreamState_ReceivedInit0;
					break;

				case StreamState_ReceivedInit0:
					if(UARTChar() == 0xE0)
						state = StreamState_CommandPhase;
					else
						state = StreamState_Uninitialized;
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
						// @@todo: real DSP
						unsigned short sample = UARTChar() << 8;

						(void)lpc;
						(void)hpc;
						(void)vfx;
						(void)identify;
						(void)attenuation;

						while(AudioFIFOIsFull())
							;	// should be a minimally-wasteful synchronization

						AudioFIFOWrite(sample, sample);
						
						if(++frameCount >= expectedCount)
							state = StreamState_Uninitialized;
					}
					break;
				}
			}
		}
	}
	else	// then transmitter
	{
		TXnRX = true;	// become a transmitter

		int wlf = (1 << 16), whf = (77 << 16), thlf = 0, thhf = 0, count = 0;
		while(1)
		{
			int lf = ksin(thlf >> 16), hf = ksin(thhf >> 16);
			
			if(count == 0)
			{
				UARTWriteBlocking(0x7F);
				UARTWriteBlocking(0xE0);
				UARTWriteBlocking(Command_FrameCountBegin);
				UARTWriteBlocking(160);
			}
			
			UARTWriteBlocking(lf);
			UARTWriteBlocking(hf);
			
			thlf += wlf;
			thhf += whf;

			if((wlf += (wlf >> 16)) > (20 << 16))
				wlf = (1 << 16);
			
			if((whf += (whf >> 16)) > (83 << 16))
				whf = (20 << 16);

			if(++count == 160)
			{
				count = 0;	// this triggers a re-sync
			}
		}
		TXnRX = false;	// become a receiver
	}
}
