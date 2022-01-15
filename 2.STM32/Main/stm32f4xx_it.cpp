#ifdef __cplusplus
 extern "C" {
#endif 
	 
#include "stm32f4xx.h"
#include "nmea_decode.h"
#include "sys.h"
 
u8 buffer[256];
static int count = 0;
u8 flag = 0;

nmeaINFO info;
nmea_decode nmea_decode; 
 
void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	u8 res;
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		res =USART_ReceiveData(USART1);//(USART1->DR);	//读取接收到的数据

		buffer[count] = res;
		count++;
		if(count == 256)
		{
			flag = 1;
			count = 0;
		}
		if(flag == 1)
		{
			info = nmea_decode.decode((const char*)&buffer[0],256);
			//printf("%d\r\n",info.fix);
			printf("正在使用的北斗卫星：%d,可见北斗卫星：%d\r\n",info.BDsatinfo.inuse,info.BDsatinfo.inview);
			if(info.fix == 1)
				printf("1:%f\r\n",info.lat);
			else if(info.fix == 2)
				printf("2:%f\r\n",info.lat);
			else if(info.fix == 3)
				printf("3:%f\r\n",info.lat);
			flag = 0;
		}
  }
}

#ifdef __cplusplus
}
#endif
