/*! \class	Communication

\brief	handles communication between devices

This class handles all between different devices.
*/

#pragma once


#ifndef Communication_h
#define Communication_h

#include "Arduino.h"
#include <Wire.h>




class Communication

{

public:

	Communication(void);
	~Communication(void);

	static int i2cread(int Sensor_Adress_, int start_, uint8_t *buffer_, int size_);
	static int i2cwrite(int Sensor_Adress_, int start_, uint8_t *pData_);

};


#endif