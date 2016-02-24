#ifndef	humidity_h
#define	humidity_h

#include <Arduino.h>
#include "sensor.h"

class Humidity : public Sensor
{
	public:
		Humidity (int _pin, float _constr);
		virtual int val ();
		// virtual String str (String prefix = " rh: ");

	private:
		// int pin;
		// float value, constr;
};

#endif
