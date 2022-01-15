#include "nmea_decode.h"
#include "sys.h"

nmea_decode::nmea_decode()
{
	
}

void nmea_decode::debug(void)
{
	/* �����������������Ϣ�ĺ��� */
    nmea_property()->trace_func = &trace;
    nmea_property()->error_func = &error;
    nmea_property()->info_func = &gps_info;
}


nmeaINFO nmea_decode::decode(const char *buff, int buffer_size)
{
	if(Debug)
		debug();
	
	//��ʼ��GPS���ݽṹ��
	nmea_zero_INFO(&info);
	nmea_parser_init(&parser);
	
	nmea_parse(&parser,buff,buffer_size,&info);	//����GPS����
	nmea_info2pos(&info,&dpos);	//����γ�����ݵ�λת��Ϊ��
	
	GMT_Convert(&info.utc,&localtime,8,1);	//��GPS�����е�ʱ��ת��Ϊ����ʱ��
	
	info.utc = localtime;
	info.lat = dpos.lat*57.3;
	info.lon = dpos.lon*57.3;
	
	nmea_parser_destroy(&parser);	//�ͷ�GPS�ṹ����
	
	return info;
}

/**
  * @brief  trace �ڽ���ʱ��������GPS���
  * @param  str: Ҫ������ַ�����str_size:���ݳ���
  * @retval ��
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
  * @brief  error �ڽ������ʱ�����ʾ��Ϣ
  * @param  str: Ҫ������ַ�����str_size:���ݳ���
  * @retval ��
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
  * @brief  error �ڽ������ʱ�����ʾ��Ϣ
  * @param  str: Ҫ������ַ�����str_size:���ݳ���
  * @retval ��
  */
void gps_info(const char *str, int str_size)
{
    uint16_t i;
    printf("Info:");
    for(i=0;i<str_size;i++)
      printf("%c",*(str+i));
    printf("\r\n");
}
