#include "humidity.h"

Humidity::Humidity (int _pin, float _constr) : Sensor (_pin, _constr)
{
// 	pin = _pin;
//	constr = _constr;
//	value = 0.0;
}


int Humidity::val ()
{
	value = (int)((analogRead(pin) * (5.0 / 1024.0) / 0.05));
	return value;
}

/*
String Humidity::str (String prefix)
{
	return String (prefix + String (value, 2));
}
*/
