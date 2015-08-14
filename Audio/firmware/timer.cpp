#include <GalagoAPI.h>
#include <LPC13xx.h>
#include <stdint.h>


using namespace Galago;

unsigned int	System_divideClockFrequencyRounded(unsigned int n, unsigned int d);

enum
{
	SEG_A =		(1 << 0),	// (1 << 7),
	SEG_F =		(1 << 1),	// (1 << 6),
	SEG_D =		(1 << 2),	// (1 << 5),
	SEG_E =		(1 << 3),	// (1 << 4),
	SEG_G =		(1 << 4),	// (1 << 3),
	SEG_C =		(1 << 5),	// (1 << 2),
	SEG_DOT =	(1 << 6),	// (1 << 1),
	SEG_B =		(1 << 7),	// (1 << 0),
};

static unsigned char const kDigitSegments[] =
{
	SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,	// 0
	SEG_B | SEG_C,	// 1
	SEG_A | SEG_B | SEG_G | SEG_E | SEG_D,	// 2
	SEG_A | SEG_B | SEG_G | SEG_C | SEG_D,	// 3
	SEG_F | SEG_B | SEG_G | SEG_C,	// 4
	SEG_A | SEG_F | SEG_G | SEG_C | SEG_D,	// 5
	SEG_A | SEG_F | SEG_G | SEG_E | SEG_C | SEG_D,	// 6
	SEG_A | SEG_B | SEG_C,	// 7
	SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,	// 8
	SEG_A | SEG_B | SEG_C | SEG_D | SEG_F | SEG_G,	// 9
	
	SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,	// A
	SEG_F | SEG_G | SEG_C | SEG_E | SEG_D,	// b
	SEG_A | SEG_F | SEG_E | SEG_D,	// C
	SEG_B | SEG_G | SEG_C | SEG_E | SEG_D,	// d
	SEG_A | SEG_F | SEG_G | SEG_E | SEG_D,	// E
	SEG_A | SEG_F | SEG_G | SEG_E,	// F

	SEG_A | SEG_B | SEG_F | SEG_G,	// 16: (deg)
	SEG_G | SEG_E | SEG_D,	// 17: c
	SEG_F | SEG_E | SEG_D | SEG_B | SEG_C,	// 18: U
	SEG_E | SEG_G,	// 19: r
	SEG_C | SEG_D | SEG_E | SEG_G,	// 20: o,
	0,	// 21: nothing
	SEG_D | SEG_E | SEG_F,	// 22: L
	SEG_D | SEG_E | SEG_F | SEG_G,	// 23: t
	SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,	// 24: H
	SEG_E,	// 25: i
};
static unsigned char const kDigits[4] = {(1 << 3), (1 << 4), (1 << 5), (1 << 0)};

enum
{
	kDigitDot = (1 << 7)
};

void microDelay(unsigned int delay)
{
	while(delay-- > 0)
		asm volatile ("nop" :::);
}

IO::Pin gLatch;

unsigned int gDigitIndex = 0;
unsigned char volatile gDigits[4] = {1, 2, 3, 4};

uint16_t volatile gMonotonicTime = 0;
unsigned int volatile gTimerFence = 0;

extern "C" 	void		IRQ_Timer0(void)
{
	*LPC1300::Timer0Interrupts = LPC1300::TimerInterrupts_Match0Flag;

	gMonotonicTime++;
	gTimerFence = 1;
}

extern "C" 	void		IRQ_Timer1(void)
{
	*LPC1300::Timer1Interrupts = LPC1300::TimerInterrupts_Match0Flag;
	
	unsigned char message[2];
	message[0] = kDigits[gDigitIndex];
	message[1] = kDigitSegments[gDigits[gDigitIndex] & 0x7F] | ((-(gDigits[gDigitIndex] >> 7)) & SEG_DOT);
	*LPC1300::SPI0Data = message[0];
	*LPC1300::SPI0Data = message[1];

	while(*LPC1300::SPI0Status & LPC1300::SPI0Status_Busy);

	gLatch = true;
	microDelay(5);
	gLatch = false;

	if(++gDigitIndex == 4)
		gDigitIndex = 0;
}

signed int lowPassFilter(signed int oldValue, signed int newValue)
{
	return(oldValue + ((newValue - oldValue) / 3));
}

int main(void)
{
	gLatch.bind(io.p4);

	gLatch.setOutput();

	gLatch = false;	// initially start in RX mode
	
	io.spi.start(1000000UL);

	
	// unset Timer1
	*LPC1300::Timer1Control = LPC1300::TimerControl_Reset;
	*LPC1300::Timer1MatchControl = 0;
	*LPC1300::ClockControl &= ~LPC1300::ClockControl_Timer1;
	
	// set Timer1
	*LPC1300::ClockControl |= LPC1300::ClockControl_Timer1;
	
	*LPC1300::Timer1Control = (LPC1300::TimerControl_Enable | LPC1300::TimerControl_Reset);
	
	*LPC1300::Timer1Prescaler = 1;
	*LPC1300::Timer1MatchControl =	LPC1300::TimerMatchControl_Match0Interrupt
									| LPC1300::TimerMatchControl_Match0Reset;
	*LPC1300::Timer1Match0 = 12000;
	
	*LPC1300::Timer1Control = LPC1300::TimerControl_Enable;
	
	*LPC1300::InterruptEnableSet1 = LPC1300::Interrupt1_Timer1;

	
	
	// unset Timer0
	*LPC1300::Timer0Control = LPC1300::TimerControl_Reset;
	*LPC1300::Timer0MatchControl = 0;
	*LPC1300::ClockControl &= ~LPC1300::ClockControl_Timer0;
	
	// set Timer0
	*LPC1300::ClockControl |= LPC1300::ClockControl_Timer0;
	
	*LPC1300::Timer0Control = (LPC1300::TimerControl_Enable | LPC1300::TimerControl_Reset);
	
	*LPC1300::Timer0Prescaler = 500;
	*LPC1300::Timer0MatchControl =	LPC1300::TimerMatchControl_Match0Interrupt
									| LPC1300::TimerMatchControl_Match0Reset;
	*LPC1300::Timer0Match0 = 12000;
	
	*LPC1300::Timer0Control = LPC1300::TimerControl_Enable;
	
	*LPC1300::InterruptEnableSet1 = LPC1300::Interrupt1_Timer0;


	unsigned char value[4] = {1, 2, 3, 4};
	while(1)
	{
		if(gTimerFence)
		{
			gTimerFence = 0;
			
			value[3]++;
			for(int i = 3; i > 0; i--)
				if(value[i] >= 10)
				{
					value[i] = 0;
					value[i - 1]++;
				}

			memcpy((void*)gDigits, value, 4);
		}

		system.wait(system.delay(10));
	}
}
