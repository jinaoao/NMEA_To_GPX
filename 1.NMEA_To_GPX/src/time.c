/*
 *
 * NMEA library
 * URL: http://nmea.sourceforge.net
 * Author: Tim (xtimor@gmail.com)
 * Licence: http://www.gnu.org/licenses/lgpl.html
 * $Id: time.c 4 2007-08-27 13:11:03Z xtimor $
 *
 */

/*! \file time.h */

#include "../inc/nmea/time.h"

#ifdef NMEA_WIN
#   pragma warning(disable: 4201)
#   pragma warning(disable: 4214)
#   pragma warning(disable: 4115)
#   include <windows.h>
#   pragma warning(default: 4201)
#   pragma warning(default: 4214)
#   pragma warning(default: 4115)
#else
#   include <time.h>
#endif

#ifdef NMEA_WIN

void nmea_time_now(nmeaTIME *stm)
{
    SYSTEMTIME st;

    GetSystemTime(&st);

    stm->year = st.wYear - 1900;
    stm->mon = st.wMonth - 1;
    stm->day = st.wDay;
    stm->hour = st.wHour;
    stm->min = st.wMinute;
    stm->sec = st.wSecond;
    stm->hsec = st.wMilliseconds / 10;
}

#else /* NMEA_WIN */

void nmea_time_now(nmeaTIME *stm)
{
	/***
    time_t lt;
    struct tm *tt;

    time(&lt);
    tt = gmtime(&lt);

    stm->year = tt->tm_year;
    stm->mon = tt->tm_mon;
    stm->day = tt->tm_mday;
    stm->hour = tt->tm_hour;
    stm->min = tt->tm_min;
    stm->sec = tt->tm_sec;
    stm->hsec = 0;
***/
	stm->year = 2021 - 1900;
	stm->mon = 0;
	stm->day = 1;
  stm->hour = 0;
  stm->min = 0;
  stm->sec = 0;
  stm->hsec = 0;
}

#endif

/**
 * \brief convert the GMT time to the local time
 * @param SourceTime the GMT time
 * @param ConvertTime the local time
 * @param GMT the number of timezone
 * @param area 1 for the east, 0 for the west
**/
void GMT_Convert(nmeaTIME *SourceTime,nmeaTIME *ConvertTime,int GMT,int area)
{
    int YY,MM,DD,hh,mm,ss;

    if(GMT==0) return;
    if(GMT>12) return;

    YY = SourceTime->year;
    MM = SourceTime->mon;
    DD = SourceTime->day;
    hh = SourceTime->hour;
    mm = SourceTime->min;
    ss = SourceTime->sec;

    if(area)
    {
        if(hh+GMT<24) hh+= GMT;
        else
        {
            hh = hh+GMT-24;
            if(MM==1 || MM==3 || MM==5 || MM==7 || MM==8 || MM==10)
            {
                if(DD<31) DD++;
                else
                {
                    DD = 1;
                    MM++;
                }
            }
            else if(MM==4||MM==6||MM==9||MM==11)
            {
                if(DD<30) DD++;
                else
                {
                    DD = 1;
                    MM++;
                }
            }
            else if(MM==2)
            {
                if((DD==29)||(DD==28 && (YY%4)==0))
                {
                    DD = 1;
                    MM++;
                }
                else DD++;
            }
            else if(MM==12)
            {
                if(DD<31) DD++;
                else
                {
                    DD = 1;
                    MM = 1;
                    YY++;
                }
            }
        }
    }
    else
    {
        if(hh>=GMT) hh -= GMT;    
        else                        
        { 
            hh = hh+24-GMT;        
            if(MM==2 || MM==4 || MM==6 || MM==8 || MM==9 || MM==11)    
            { 
                if(DD>1) DD--; 
                else 
                { 
                    DD = 31; 
                    MM --; 
                } 
            } 
            else if(MM==5 || MM==7 || MM==10 || MM==12)             
            { 
                if(DD>1) DD--; 
                else 
                { 
                    DD = 30; 
                    MM --; 
                } 
            } 
            else if(MM==3)   
            { 
                if((DD==1) && (YY%4)==0)                    
                { 
                    DD = 28; 
                    MM --; 
                } 
                else DD--; 
            } 
            else if(MM==1)    
            { 
                if(DD>1) DD--; 
                else        
                {               
                    DD = 31; 
                    MM = 12; 
                    YY --; 
                } 
            } 
        } 
    }

    ConvertTime->year = YY+1900;
    ConvertTime->mon = MM+1;
    ConvertTime->day = DD;
    ConvertTime->hour = hh;
    ConvertTime->min = mm;
    ConvertTime->sec = ss;
}
