/*! \class	PressureSensor

\brief	handles the PressureSensor

This class handles the pressure sensor and its data.
*/

#pragma once


#ifndef PressureSensor_h
#define PressureSensor_h


#define PRESSURE_SENSOR_ADRESS 0x38   // = 0b111000
#define OUTMIN 0x0666
#define OUTMAX 0x6CCC
#define PMAX 25
#define SENSIVITY 1048.56
#define INVALIDPRESSURE -1


#include "Communication.h"


class PressureSensor

{

public:

	PressureSensor(void);
	~PressureSensor(void);

	void convertRawPressureToPressure(int rawPressure_);
	inline int getSensorData() {error = Communication::i2cread(PRESSURE_SENSOR_ADRESS, 1, &rawPressure, 1);};
	inline double getPressure() {return PressureSensor::Pressure;};



private:

	int error;
	uint8_t rawPressure;
	double Pressure;

};


#endif

