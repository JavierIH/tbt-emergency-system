#ifndef	relay_h
#define relay_h

#include <Arduino.h>

class Relay
{
	public:
		Relay (int _pin);
		int state ();
		void on ();
		void off ();

	private:
		int s;
		int pin;
};

#endif
