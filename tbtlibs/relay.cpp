#include <relay.h>

Relay::Relay (int _pin)
{
	pin = _pin;
	pinMode (pin, OUTPUT);
	s = LOW;
	digitalWrite (pin, s);
}

void Relay::on ()
{
	s = HIGH;
	digitalWrite (pin, s);
}

void Relay::off ()
{
	s = LOW;
	digitalWrite (pin, s);
}

int Relay::state ()
{
	return s;
}
