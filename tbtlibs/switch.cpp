#include <switch.h>

Switch::Switch (int _pin, int _constr) : Sensor (_pin, _constr)
{
	pin = _pin;
	pinMode (pin, INPUT_PULLUP);
	constr = _constr;
}

int Switch::val ()
{
	value = digitalRead (pin);
}

/*
String Switch::str (String prefix)
{
	return String (prefix + String (s, DEC));
}

bool Switch::c ()
{
	if (s == constr)
		return true;

	return false;
}
*/
