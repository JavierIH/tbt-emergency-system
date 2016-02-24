#include "temperature.h"

Temperature::Temperature (int _pin, float _constr) : Sensor (_pin, _constr)
{
//	pin = _pin;	
//	_constr = _constr;
//	value = 0.0;
}

int Temperature::val ()
{
	value = (int)((analogRead(pin) * (5.0 / 1024.0) / 0.05) - 40);
	return value;
}

// String Temperature::str (String prefix)
//{
//	return String (prefix + String (value, 2));
//}
