#ifndef	temperature_h
#define	temperature_h

#include <Arduino.h>
#include "sensor.h"

class Temperature : public Sensor
{
	public:
		Temperature (int _pin, float _constr);
		virtual int val ();
		// String str (String prefix = " t: ");

	// private:
	// 	int pin, value, constr;
};

#endif
