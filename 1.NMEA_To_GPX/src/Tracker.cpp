#include "../inc/Tracker.h"

Tracker::Tracker()
{

}

void Tracker::debug(void)
{
    nmea_property()->trace_func = &trace;
    nmea_property()->error_func = &error;
    nmea_property()->info_func = &gps_info;
}

void Tracker::GPX_Set_Header()
{
    gpx.setMetaDesc("nmea2GPX");
    gpx.setName("track name");
    gpx.setDesc("Written by jinao");
    gpx.setSrc("Tracker");
}

void Tracker::Tracker_init(fstream *file)
{
    *file << gpx.getOpen();

    GPX_Set_Header();

    *file << gpx.getMetaData();
    *file << gpx.getTrackOpen();
    *file << gpx.getInfo();
    *file << gpx.getTrackSegOpen();

    nmea_zero_INFO(&info);
    nmea_parser_init(&parser);
}

void Tracker::Tracker_NMEAFile_GPXFile(fstream *nmeafile, fstream *gpxfile)
{
    char buff[2048];

    if(Debug)
        debug();
    Tracker_init(gpxfile);

    while(!(nmeafile->eof()))
    {
        nmeafile->read(&buff[0],100);
        nmea_parse(&parser,&buff[0],100,&info);
        nmea_info2pos(&info,&dpos);

        GMT_Convert(&info.utc,&localtime,8,1);

        if(info.sig == 1)
        {
            string date = get_num_nwidth(localtime.year,2) + "-" + get_num_nwidth(localtime.mon,2) + "-" + get_num_nwidth(localtime.day,2);
            string time = get_num_nwidth(localtime.hour,2) + ":" + get_num_nwidth(localtime.min,2) + ":" + get_num_nwidth(localtime.sec,2);

            *gpxfile << gpx.getPt(GPX_TRKPT,to_string(dpos.lat*57.3),to_string(dpos.lon*57.3),to_string(info.elv),date,time);
        }
    }

    Tracker_Close(gpxfile);

}

void Tracker::Tracker_Close(fstream *file)
{
    *file << gpx.getTrackSegClose();
    *file << gpx.getTrackClose();
    *file << gpx.getClose();

    nmea_parser_destroy(&parser);
}

string get_num_nwidth(int val,int prec)
{
    stringstream ss;
    ss << setw(prec) << setfill('0') << val;
    return ss.str();
}

/**
  * @brief  trace 在解码时输出捕获的GPS语句
  * @param  str: 要输出的字符串，str_size:数据长度
  * @retval 无
  */
void trace(const char *str, int str_size)
{
    uint16_t i;
    printf("Trace:");
    for(i=0;i<str_size;i++)
      printf("%c",*(str+i));

    printf("\r\n");
}

/**
  * @brief  error 在解码出错时输出提示消息
  * @param  str: 要输出的字符串，str_size:数据长度
  * @retval 无
  */
void error(const char *str, int str_size)
{
    uint16_t i;
    printf("Error:");
    for(i=0;i<str_size;i++)
      printf("%c",*(str+i));
    printf("\r\n");
}

/**
  * @brief  error 在解码出错时输出提示消息
  * @param  str: 要输出的字符串，str_size:数据长度
  * @retval 无
  */
void gps_info(const char *str, int str_size)
{
    uint16_t i;
    printf("Info:");
    for(i=0;i<str_size;i++)
      printf("%c",*(str+i));
    printf("\r\n");
}
