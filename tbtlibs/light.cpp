#include <light.h>

Light::Light (int _pin, int _constr) : Sensor (_pin, _constr)
{
	//
}

bool Light::state ()
{

	if (val() < constr)
		return false;
	
	return true;
}
