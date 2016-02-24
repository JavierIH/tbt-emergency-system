#ifndef	logger_h
#define	logger_h

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

const int chipSelect = 4;

class Logger
{
	public:
		Logger ();
		int init ();
		int write (String filename, String data);

	private:
		File dataFile;
};

#endif
