#include "nmea_decode.h"
#include "sys.h"

nmea_decode::nmea_decode()
{
	
}

void nmea_decode::debug(void)
{
	/* 设置用于输出调试信息的函数 */
    nmea_property()->trace_func = &trace;
    nmea_property()->error_func = &error;
    nmea_property()->info_func = &gps_info;
}


nmeaINFO nmea_decode::decode(const char *buff, int buffer_size)
{
	if(Debug)
		debug();
	
	//初始化GPS数据结构体
	nmea_zero_INFO(&info);
	nmea_parser_init(&parser);
	
	nmea_parse(&parser,buff,buffer_size,&info);	//解码GPS数据
	nmea_info2pos(&info,&dpos);	//将经纬度数据单位转化为度
	
	GMT_Convert(&info.utc,&localtime,8,1);	//将GPS数据中的时间转换为北京时间
	
	info.utc = localtime;
	info.lat = dpos.lat*57.3;
	info.lon = dpos.lon*57.3;
	
	nmea_parser_destroy(&parser);	//释放GPS结构数据
	
	return info;
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
