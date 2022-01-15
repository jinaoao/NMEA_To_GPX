#ifndef __GPX_H
#define __GPX_H

//#include <iostream>
#include <string>
using namespace std;

#define _GPX_HEAD "<gpx version=\"1.1\" creator=\"GPX Lib\"\n xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n xmlns=\"http://www.topografix.com/GPX/1/1\"\n xsi:schemaLocation=\"http://www.topografix.com/GPX/1/1 http://www.topografix.com/GPX/1/1/gpx.xsd\"\n>\n"
#define _GPX_TAIL               "</gpx>\n"
#define _GPX_META_HEAD          "<metadata>\n"
#define _GPX_META_TAIL          "</metadata>\n"
#define _GPX_TRAK_HEAD          "<trk>\n"
#define _GPX_TRAK_TAIL          "</trk>\n"
#define _GPX_TRKSEG_HEAD        "<trkseg>\n"
#define _GPX_TRKSEG_TAIL        "</trkseg>\n"
#define _GPX_PT_HEAD            "<trkpt lat=\""
#define _GPX_PT_TAIL            "</trkpt>\n"

// Property Tags
#define _GPX_NAME_HEAD          "<name>"
#define _GPX_NAME_TAIL          "</name>\n"
#define _GPX_DESC_HEAD          "<desc>"
#define _GPX_DESC_TAIL          "</desc>\n"
#define _GPX_SYM_HEAD           "<sym>"
#define _GPX_SYM_TAIL           "</sym>\n"
#define _GPX_ELE_HEAD           "<ele>"
#define _GPX_ELE_TAIL           "</ele>\n"
#define _GPX_SRC_HEAD           "<src>"
#define _GPX_SRC_TAIL           "</src>\n"
#define _GPX_TIME_HEAD          "<time>"
#define _GPX_TIME_TAIL          "</time>\n"

// 'Public' Tags
#define GPX_TRKPT               "trkpt"
#define GPX_WPT                 "wpt"
#define GPX_RTEPT               "rtept"


class GPX
{
    public:
      GPX();
      string getOpen();
      string getClose();
      string getMetaData();
      string getTrackOpen();
      string getTrackClose();
      string getTrackSegOpen();
      string getTrackSegClose();
      string getInfo();
      string getPt(string typ, string lon, string lat, string ele, string date, string time);
      void setMetaName(string name);
      void setMetaDesc(string desc);
      void setName(string name);
      void setDesc(string desc);
      void setSym(string sym);
      void setSrc(string src);
    private:
    //variables
      string _metaName;
      string _metaDesc;
      string _name;
      string _desc;
      string _sym;
      string _src;

      string wrapCDATA(string input);
};


#endif
