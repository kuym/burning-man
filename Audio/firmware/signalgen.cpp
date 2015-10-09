#include <GalagoAPI.h>
#include <LPC13xx.h>

using namespace Galago;

unsigned int	System_divideClockFrequencyRounded(unsigned int n, unsigned int d);

int main(void)
{
	system.setCoreFrequency(72000000UL);
	
	// timer shutdown
	*LPC1300::Timer1Control = LPC1300::TimerControl_Reset;
	*LPC1300::Timer1MatchControl = 0;
	*LPC1300::ClockControl &= ~LPC1300::ClockControl_Timer1;
	
	io.p5.setOutput();
	io.p5 = true;
	io.p5.setPWM();
	
	// set up PWM on p5 (timer1 match0) and interrupt for audio samples
	*LPC1300::ClockControl |= LPC1300::ClockControl_Timer1;
	
	*LPC1300::Timer1Control = (LPC1300::TimerControl_Enable | LPC1300::TimerControl_Reset);
	
	*LPC1300::Timer1Prescaler = 0;
	*LPC1300::Timer1MatchControl = LPC1300::TimerMatchControl_Match3Reset;
	*LPC1300::Timer1ExternalMatch = LPC1300::TimerExternalMatch_Match0Set;
	*LPC1300::Timer1PWMControl = LPC1300::TimerPWMControl_Match0;
	
	*LPC1300::Timer1Match3 = System_divideClockFrequencyRounded(system.getMainClockFrequency(), 500000);	// frequency
	
	*LPC1300::Timer1Match0 = *LPC1300::Timer1Match3 >> 1;	// duty cycle (initially 50%)
	
	*LPC1300::Timer1Control = LPC1300::TimerControl_Enable;
	
	while(true)
	{
		//unsigned short freq = io.a0.readAnalog();
		//unsigned short duty = io.a1.readAnalog();

		// do nothing
	}
}
