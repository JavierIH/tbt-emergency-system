#ifndef	switch_h
#define switch_h

#include <Arduino.h>
#include "sensor.h"

class Switch : public Sensor
{
	public:
		Switch (int _pin, int _constr = 0);
		virtual int val ();
};

#endif
