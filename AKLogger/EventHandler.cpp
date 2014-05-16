#include "EventHandler.h"


EventHandler::EventHandler(void)
{
}


EventHandler::~EventHandler(void)
{
}

/*! \brief	calls all required functions

*/
void EventHandler::EventCaller(){

	int a;
	noInterrupts();
	a = myPressureSensor.getSensorData();
	interrupts();
	myPressureSensor.convertPressureToSpeed(a);


	time = millis();
	Serial.print(time);
	Serial.print("\t");
	Serial.println(myPressureSensor.getPressure());

}