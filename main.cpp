#include <pigpio.h>
#include<thread>
#include "UltrasonicSensor.h"
#include<iostream>
// LED Pin - wiringPi pin 0 is BCM_GPIO 17.
// we have to use BCM numbering when initializing with wiringPiSetupSys
// when choosing a different pin number please use the BCM numbering, also
// update the Property Pages - Build Events - Remote Post-Build Event command 
// which uses gpio export for setup for wiringPiSetupSys
#define	LED	17

int main(void)
{
	cout << "Welcome to C++ UltraSonic Sensor Tutorial!" << endl;

	//Initialise GPIO 
	if (gpioInitialise() < 0)
	{
		cout << "GPIO Initialisation failed!" << endl;
	}
	//Initialise Buzzuer
	int buzzer_pin = 13;
	gpioSetMode(buzzer_pin, PI_OUTPUT);
	gpioWrite(buzzer_pin, PI_LOW);

	UltrasonicSensor myUSensor(19,26,0);
	while (true)
	{
		int distance_cm = myUSensor.Get_Distance_cm(4);
		if (distance_cm != -1)
		{
			cout << "Measured Distance (cm): " << distance_cm << "\t." << endl;
			

			if (distance_cm < 10)
			{
				gpioWrite(buzzer_pin, PI_HIGH);
			}
			else
			{
				gpioWrite(buzzer_pin, PI_LOW);
			}
		}

		
		
	}
	
	return 0;
}