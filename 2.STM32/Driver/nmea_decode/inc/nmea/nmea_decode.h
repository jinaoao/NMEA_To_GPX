#ifndef __NMEA_DECODE_H
#define __NMEA_DECODE_H

#include "nmea.h"

class nmea_decode
{
	private:
		nmeaINFO info;
		nmeaPARSER parser;
		nmeaPOS dpos;
		nmeaTIME localtime;
	
	public:
		nmea_decode();
		nmeaINFO decode(const char *buff, int buffer_size);
		void debug(void);
};

#define Debug 1

void trace(const char *str, int str_size);
void error(const char *str, int str_size);
void gps_info(const char *str, int str_size);

#endif
