#ifndef maplin_h
#define maplin_h

/*
   based on the code found on

	http://blog.kkessler.com/2012/06/21/sparkfun-weather-station/
*/

#include <Arduino.h>
#include "sensor.h"

#define	WIND_FACTOR	2.4

class Anemometer : public Sensor
{
	public:
		Anemometer (int _pin, int _constr, long _average);

		virtual int val ();
		int getGust ();

	private:
		int gust;
		long average;
		// interrpupt callback has to be static
		static void anemometerClick ();
};

#endif
