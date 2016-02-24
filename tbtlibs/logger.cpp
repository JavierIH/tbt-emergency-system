#include <logger.h>

Logger::Logger ()
{
	// 
}

int Logger::init ()
{
	if (!SD.begin(chipSelect)) 
	{	
		return 1;		 
	}

	return 0;
}

int Logger::write (String filename, String data)
{
	char fname[30];
	filename.toCharArray (fname, filename.length() + 1);

	dataFile = SD.open(fname, FILE_WRITE);

	if (dataFile) 
	{
		dataFile.println(data);
		dataFile.close();
		// Serial.println(data);
		return 0;
	}
	else 
	{
		return 1;		
	}
}
