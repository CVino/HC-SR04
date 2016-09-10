#include <iostream>
#include <pigpio.h>
#include "libUS.h"
using namespace std;

int trigger = 4;
int echo = 17;

int main()
{
	if (gpioInitialise() <0)
	{
		cout <<"Initialisation of the GPIO Failed. /n Closing program..."<< endl;
		return -1;
	}
	
	//CHECK OUTPUT
    gpioWrite(trigger, 1);
    gpioSleep(PI_TIME_RELATIVE, 1, 0);
    gpioWrite(trigger, 0);
    
    UltraSound US;
    US.Init(trigger, echo);

    while(1){
		gpioSleep(PI_TIME_RELATIVE, 0, 500000);
        cout << "Distance is " << US.GetDistance(30000) << " cm." << endl; //If distance > 4.7 meters, distance =~ 34m (200ms pulse)
        
    }
}
