#ifndef	sensor_h
#define sensor_h

#include <Arduino.h>

class Sensor
{
	public:
		Sensor (int _pin, int _constr);
		virtual int val ();
		virtual bool state ();
		virtual String str (String prefix = ";");

	protected:
		int pin, value, constr;
};

#endif
