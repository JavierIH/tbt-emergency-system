#include "anemometer.h"

/*
   variabled used in static function should be defned here, not in header
*/

volatile unsigned long anem_count = 0;
volatile unsigned long anem_last = 0;
volatile unsigned long anem_min = 0xffffffff;

Anemometer::Anemometer (int pin, int _constr, long _average) : Sensor (pin, constr)
{
	constr = _constr;
	average = _average;
	// enable the internal pullup resistor
	pinMode (pin, INPUT_PULLUP);
	// i.e. anemomenter has to be connected between GND and pin
	attachInterrupt (digitalPinToInterrupt(pin), anemometerClick, FALLING);
	value = 0.0;
	gust = 0.0;
}

int Anemometer::val ()		
{
	unsigned long reading = anem_count; 	
	anem_count = 0;  
	value = (int)((WIND_FACTOR*reading)/(average/1000));
	return value;
}

int Anemometer::getGust()	
{
	unsigned long reading = anem_min;
	anem_min = 0xffffffff;
	double time = reading/1000000.0;
	gust = (int)((1/(reading/1000000.0))*WIND_FACTOR);
	return gust;
}

void Anemometer::anemometerClick()	
{
	long thisTime=micros()-anem_last;
	
	anem_last=micros();
	
	if(thisTime>500)
	{
		anem_count++;

		if(thisTime<anem_min)
		{
			anem_min=thisTime;	
		}		
	}	
}
