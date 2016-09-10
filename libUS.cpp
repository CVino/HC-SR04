#include <iostream>
#include <pigpio.h>
#include "libUS.h"


void UltraSound::Init(unsigned int trigger, unsigned int echo)
{
    this->trigger=trigger;
    this->echo=echo;
    gpioSetMode(trigger,PI_OUTPUT); 
    gpioSetMode(echo,PI_INPUT); 
    gpioWrite(trigger, 0);
    gpioSleep(PI_TIME_RELATIVE, 0.5, 0);
}

double UltraSound::GetDistance(unsigned int timeout)
{
	endTimeUsec=0;
	gpioWrite(trigger, 1);
	gpioDelay(10);
	gpioWrite(trigger, 0);

    now=gpioTick();

    while (endTimeUsec== 0 && gpioTick()-now<timeout)
    {
        RecordPulseLength();
	}

    DifferenceTimeUsec = endTimeUsec - startTimeUsec;
    //distanceCm = 50*((DifferenceTimeUsec/1000000.0)*340.29);
    distanceCm = (double)DifferenceTimeUsec/58.7734;
	
	if (endTimeUsec!= 0)
		return distanceCm;
    else
		return 0;
}

void UltraSound::RecordPulseLength()
{
    startTimeUsec = gpioTick();
    while ( gpioRead(echo) == 1 )
    {
		endTimeUsec = gpioTick();
	}
}
