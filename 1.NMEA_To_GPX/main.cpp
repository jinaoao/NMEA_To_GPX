#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include ".\inc\GPX.h"
#include ".\inc\nmea\nmea.h"
#include ".\inc\Tracker.h"

Tracker tracker;

int main()
{
    fstream gpx_file,nmea_file;

    nmea_file.open("gpslog.txt",ios::in|ios::binary);
    gpx_file.open("gpx_test2.gpx",ios::out|ios::binary);

    tracker.Tracker_NMEAFile_GPXFile(&nmea_file,&gpx_file);

    nmea_file.close();
    gpx_file.close();

    return 0;
}




