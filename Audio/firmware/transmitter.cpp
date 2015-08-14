#include <GalagoAPI.h>
#include <LPC13xx.h>
#include <stdint.h>
#include "audio-common.h"


using namespace Galago;

unsigned int	System_divideClockFrequencyRounded(unsigned int n, unsigned int d);

unsigned int const			kAudioBufferLength = 160;
volatile unsigned char		gAudioBuffer[kAudioBufferLength];
volatile unsigned int		gAudioTail, gAudioFill;


extern "C" 	void		IRQ_Timer1(void)
{
	*LPC1300::Timer1Interrupts = LPC1300::TimerInterrupts_Match0Flag;
}

void		AudioTxFIFOInit(void)
{
	gAudioTail = 0;
	gAudioFill = 0;
}

unsigned int	AudioTxFIFOCount(void)
{
	InterruptsDisable();

	int full = gAudioFill;

	InterruptsEnable();

	return(full);
}

bool		AudioTxFIFOIsFull(void)
{
	return(AudioTxFIFOCount() >= kAudioBufferLength);
}

void		AudioTxFIFOWrite(unsigned char compressedDatum)
{
	InterruptsDisable();
	unsigned int tail = gAudioTail, fill = gAudioFill;

	if(fill >= kAudioBufferLength)
	{
		gAudioTail = tail = (tail < (kAudioBufferLength - 1))? (tail + 1) : 0;
		fill -= 1;
	}

	unsigned int h = ((tail + fill) >= kAudioBufferLength)?
			(tail + fill - kAudioBufferLength)
		:	(tail + fill);

	gAudioBuffer[h] = compressedDatum;
	gAudioFill = fill + 1;
	InterruptsEnable();
}

unsigned char	AudioTxFIFORead(void)
{
	InterruptsDisable();

	unsigned char datum = gAudioBuffer[gAudioTail++];
	
	gAudioFill--;
	if(gAudioTail >= kAudioBufferLength)
		gAudioTail = 0;
	
	InterruptsEnable();

	return(datum);
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

/*
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
*/

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


int main(void)
{
	// we will use:
	//   - timer1 as a 96KHz timebase, highest interrupt priority
	//   - systick as second-highest interrupt priority
	//   - the UART asynchronously, third-highest interrupt priority
	//   - the SPI asynchronously (via FIFO) but without interrupts

	IO::Pin TXnRX;

	TXnRX.bind(io.rts);
	
	TXnRX = false;	// initially start in RX mode
	
	system.setCoreFrequency(72000000UL);

	system.setClockOutputFrequency(72000000UL);

	io.p1.setMode(IO::Pin::ClockOutput);
	
	AudioTxFIFOInit();
	//UARTInit();

	io.txd.setMode(IO::Pin::UART);
	io.rxd.setMode(IO::Pin::UART);
	
	// previously 4, yielding 1.125Mbps
	// now 12, resulting in 375kbps
	io.serial.startWithExplicitRatio(12, 0, 1, IO::UART::Default);

	TXnRX = true;	// become a transmitter

	unsigned int frameSize = 320;

	while(1)
	{
		// when we tip, burst-transmit the whole frame
		if(AudioTxFIFOCount() >= frameSize)
		{
			UARTWriteBlocking(0x7F);
			UARTWriteBlocking(0xE0);
			UARTWriteBlocking(Command_FrameCountBegin);
			UARTWriteBlocking(frameSize >> 1);

			for(unsigned int i = 0; i < frameSize; i++)
				UARTWriteBlocking(AudioTxFIFORead());

			// frame is complete
		}
	}
}
