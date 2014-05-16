/*! \class	EventHandler

\brief	handles regular Events

This class handles all regular called Events.
*/


#pragma once

#ifndef EVENTHANDLER_h
#define EVENTHANDLER_h

#include "Arduino.h"
#include "Communication.h"
#include "PressureSensor.h"





class EventHandler
{
public:

	EventHandler(void);
	~EventHandler(void);

	void EventCaller();

private:

	PressureSensor myPressureSensor;

	long time;
};




#endif