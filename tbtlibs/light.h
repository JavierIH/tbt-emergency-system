#ifndef light_h
#define light_h

/*
   photoresistor  pin  GND
   10k            pin  5V
*/

#include <Arduino.h>
#include "sensor.h"

class Light : public Sensor
{
	public:
		Light (int _pin, int _constr);
		virtual bool state ();
};

#endif
