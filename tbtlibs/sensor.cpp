#include "sensor.h"

Sensor::Sensor (int _pin, int _constr)
{
	pin = _pin;
	constr = _constr;
	value = 0.0;
}

int Sensor::val ()
{
	value = analogRead(pin);
	return value;
}

bool Sensor::state ()
{
	if (val() == constr)
		return false;

	return true;
}

String Sensor::str (String prefix)
{
	return String (prefix + String (val(), DEC));
}
