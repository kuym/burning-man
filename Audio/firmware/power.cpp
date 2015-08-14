#include <GalagoAPI.h>
#include <LPC13xx.h>
#include <stdint.h>


using namespace Galago;

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
	SEG_G,	// 26: -
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

enum
{
	Error_noError,
	Error_Unknown,
	Error_HighVoltage,
	Error_LowVoltage,
	Error_HighCurrent,
	Error_OverTemp,

	Error__last
};

static char const* kMessages[] =
{
	"\x09\x14\x14\x0d",	// Error_noError:		9ood
	"\x0b\x0a\x0d\x15",	// Error_Unknown:		bad
	"\x18\x19\x0b\x17",	// Error_HighVoltage:	Hibt
	"\x16\x14\x0b\x17",	// Error_LowVoltage:	Lobt
	"\x18\x19\x0c\x13",	// Error_HighCurrent:	HiCr
	"\x18\x14\x17\x15",	// Error_OverTemp:		Hot
};

signed int lowPassFilter(signed int oldValue, signed int newValue)
{
	return(oldValue + ((newValue - oldValue) / 3));
}

int toVolts(unsigned int value)
{
	// with a 1:6 voltage divider * 3301mV/full-scale / 10
	// Vbat >-- 50k -(adc)- 10k --| GND
	// ADC is 3301/65536 V/lsb
	// 2048 worked well on the breadboard
	unsigned int volts = (value * 2618) >> 16;

	if(volts > 9999)
		volts = 9999;

	return(volts);
}

int toAmps(unsigned int value)
{
	// with a 0.16V/A transfer function:
	// 10mR * (1 + 15/1)amp
	// ADC is 3301/65536 V/lsb
	unsigned int amps = (value * 2940) >> 16;	// was 2700

	if(amps > 9999)
		amps = 9999;

	return(amps);
}

int	toDegC(unsigned int value)
{
	// MCP9700 is 500mV + 10mV/degC
	// this results in 1/10 * degC readings
	return((value * 3330 - (600 << 16)) >> 16);
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

	
	IO::Pin vSense, iSense, tSense, loadEnable, extError;

	vSense.bind(io.a0);
	vSense.setAnalog();

	iSense.bind(io.a1);
	iSense.setAnalog();

	tSense.bind(io.a2);
	tSense.setAnalog();

	loadEnable.bind(io.p1);
	loadEnable.setOutput(IO::Pin::PullDown);
	loadEnable = false;

	extError.bind(io.p2);
	extError.setInput(IO::Pin::PullUp);

	enum
	{
		Mode__first = 0,

		Mode_StatusWord = Mode__first,
		Mode_Volts,
		Mode_Amps,
		Mode_Amps2,
		Mode_Amps3,
		Mode_DegC,
		Mode_DegF,

		Mode__last,
	};

	int mode = 0, modeSwitch = 0, error = 0, errState = 0;
	unsigned int vSupply = 0, iSupply = 0, temperature = 0, errCode = 0, bootupGracePeriod = 20, loadCooldown = 5;
	
	while(1)
	{
		vSupply = lowPassFilter(vSupply, vSense.readAnalog());	// value between 0 and 65536
		iSupply = lowPassFilter(iSupply, iSense.readAnalog());	// value between 0 and 65536
		temperature = lowPassFilter(temperature, tSense.readAnalog());	// value between 0 and 65536

		if(bootupGracePeriod > 0)
		{
			bootupGracePeriod--;

			memcpy((void*)gDigits, (bootupGracePeriod > 10)? "\x1A\x1A\x1A\x1A" : "\x13\x05\x0E\x17", 4);	// "----" then "r5Et"
		}
		else
		{
			if(loadCooldown > 0)
				if(--loadCooldown == 0)
					loadEnable = true;

			if(!extError.read())	// unknown HW error
			{
				if(error < 40)	error = 40;
				errCode = Error_Unknown;
				
				loadEnable = false;
				loadCooldown = 60;
			}
			
			if(toDegC(temperature) > 450)	// 45degC
			{
				if(error < 120)	error = 120;
				errCode = Error_OverTemp;
			}
			
			if(toAmps(iSupply) > 1500)	// 15A
			{
				if(error < 120)	error = 120;
				errCode = Error_HighCurrent;

				loadEnable = false;
				loadCooldown = 60;
			}

			if(toVolts(vSupply) > 1600)	// 16V
			{
				if(error < 120)	error = 120;
				errCode = Error_HighVoltage;
				
				loadEnable = false;
				loadCooldown = 60;
			}

			if(toVolts(vSupply) < 1000)	// 10V
			{
				if(error < 120)	error = 120;
				errCode = Error_LowVoltage;
				
				loadEnable = false;
				loadCooldown = 60;
			}
			
			if(errState)
			{
				unsigned int messageID = (errCode < (unsigned int)Error__last)? errCode : (unsigned int)Error_Unknown;
				memcpy((void*)gDigits, kMessages[messageID], 4);
				// light no LEDs
			}
			else
			{
				switch(mode)
				{
				case Mode_StatusWord:
					{
						char value[4] = {14, 19, 19, (unsigned char)errCode};	//"Err-"
						memcpy((void*)gDigits, error? value : kMessages[0], 4);
						// light no LEDs
					}
					break;

				case Mode_Volts:	// supply voltage
					{
						unsigned int volts = toVolts(vSupply);

						unsigned char value[4];
						for(int i = 3; i >= 0; i--)
						{
							value[i] = volts % 10;
							volts /= 10;
						}

						value[1] |= kDigitDot;
						
						memcpy((void*)gDigits, value, 4);

						// light 'volts' LED
					}
					break;

				case Mode_Amps:	// supply current
				case Mode_Amps2:
				case Mode_Amps3:
					{
						unsigned int amps = toAmps(iSupply);	// returns centiamps

						unsigned char value[4];
						if(amps >= 1000)
						{
							for(int i = 3; i >= 0; i--)
							{
								value[i] = amps % 10;
								amps /= 10;
							}
							value[1] |= kDigitDot;
						}
						else
						{
							for(int i = 2; i >= 0; i--)
							{
								value[i] = amps % 10;
								amps /= 10;
							}
							value[0] |= kDigitDot;
						}
						value[3] = 0xA;
						
						memcpy((void*)gDigits, value, 4);

						// light 'amps' LED
					}
					break;

				case Mode_DegC:	// temperature C
				case Mode_DegF:	// temperature F
					{
						unsigned int degrees = toDegC(temperature);

						if(degrees > 999)
							degrees = 999;

						if(mode == Mode_DegF)
						{
							// convert to degF
							degrees = (degrees * 46 + 8192) >> 8;
						}
						
						unsigned char value[4];
						for(int i = 2; i >= 0; i--)
						{
							value[i] = degrees % 10;
							degrees /= 10;
						}

						value[3] = (mode == Mode_DegC)? 17 : 15;	// 'c' or 'F'

						// degC gets a dot: xx.xc
						// degF does not: xxxF
						if(mode == Mode_DegC)
							value[1] |= kDigitDot;
						else if(value[0] == 0)
							value[0] = 21;
						
						memcpy((void*)gDigits, value, 4);

						// light no LEDs
					}
					break;
				}
			}

			if(++modeSwitch == 8)
			{
				modeSwitch = 0;
				if(error && !errState)
					errState = 1;
				else
				{
					errState = 0;
					if(++mode == Mode__last)
						mode = Mode__first;
				}
			}

			// errors fade over time
			if(error > 0)
				if(--error == 0)	// when it fades out complete, reset the code
					errCode = 0;
		}

		system.wait(system.delay(250));
	}
}
