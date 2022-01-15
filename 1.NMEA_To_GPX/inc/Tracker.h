#ifndef __TRACKER_H
#define __TRACKER_H

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "..\inc\GPX.h"
#include "..\inc\nmea\nmea.h"

class Tracker
{
private:
    nmeaINFO info;
    nmeaPARSER parser;
    nmeaPOS dpos;
    nmeaTIME localtime;
    string tracker_name;
    GPX gpx;
    void GPX_Set_Header();

public:
    Tracker();
    void Tracker_init(fstream *file);
    void Tracker_NMEAFile_GPXFile(fstream *nmeafile, fstream *gpxfile);
    void Tracker_Close(fstream *file);
    void debug(void);
};

#define Debug 1

void trace(const char *str, int str_size);
void error(const char *str, int str_size);
void gps_info(const char *str, int str_size);

string get_num_nwidth(int val,int prec);

#endif // __TRACKER_H
