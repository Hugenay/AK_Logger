#include "PressureSensor.h"


PressureSensor::PressureSensor(void)
{

	Pressure = INVALIDPRESSURE;
	error = -1;

}


PressureSensor::~PressureSensor(void)
{
}


/*! \brief	Function to convert the raw Pressure to real Pressure ans Speed
		
	\param rawPressure_ raw Presssure value form sensor
*/
void PressureSensor::convertRawPressureToPressure(int rawPressure_){

	if (error == 0){

		Pressure = (rawPressure_ - OUTMIN) / SENSIVITY;

	}
}


