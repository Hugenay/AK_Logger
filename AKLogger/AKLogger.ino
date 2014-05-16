/* \brief	AK-X Datalogger

Die Datenloggersoftware

*/


#include <Metro.h>
#include <Wire.h>
#include "EventHandler.h"


#define TIMERFREQ 500


EventHandler myEventHandler;
Metro myTimer = Metro(TIMERFREQ);



void setup()
{
	
	Serial.begin(115200);
	delay(100);
	Serial.print("Time");
	Serial.print("\t");
	Serial.println("Pressure");
	delay(100);
	Serial.println("******************************************");
	delay(100);

	
}

void loop()
{

	if (myTimer.check() == 1){

		myEventHandler.EventCaller();

	}
	
}

