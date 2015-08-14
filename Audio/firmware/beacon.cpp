#include <GalagoAPI.h>
#include <LPC13xx.h>
#include <stdint.h>


using namespace Galago;

int main(void)
{
	IO::Pin red, green, blue, white, dutyCycle;

	red.bind(io.p1);
	red.setOutput(IO::Pin::PullDown);
	red = false;
	
	green.bind(io.p2);
	green.setOutput(IO::Pin::PullDown);
	green = false;
	
	blue.bind(io.p3);
	blue.setOutput(IO::Pin::PullDown);
	blue = false;
	
	white.bind(io.p4);
	white.setOutput(IO::Pin::PullDown);
	white = false;

	dutyCycle.bind(io.a0);
	dutyCycle.setAnalog();

	int color = 0;
	while(1)
	{
		int onTime = (dutyCycle.readAnalog() * 500) >> 17;

		if(onTime < 1)
			onTime = 1;

		if(onTime > 249)
			onTime = 249;

		switch(color)
		{
		case 0: red = true;		break;
		case 1: green = true;	break;
		case 2: blue = true;	break;
		case 3: white = true;	break;
		}

		system.wait(system.delay(onTime));	// on-period

		switch(color)
		{
		case 0: red = false;	break;
		case 1: green = false;	break;
		case 2: blue = false;	break;
		case 3: white = false;	break;
		}
		if(++color == 4)
			color = 0;
		
		system.wait(system.delay(250 - onTime));	// off-period
	}
}
