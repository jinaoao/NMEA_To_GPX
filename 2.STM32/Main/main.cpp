#include "sys.h"
#include "led.h"  
#include "delay.h"
#include "usart.h" 
#include "lcd_3.5tft.h"

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	
	delay_init(84);
	uart_init(115200);
	delay_ms(50);
	
	LED_Init();		// LED��ʼ��
	LCD_Init();

	LED1_OFF;
	
	while(1)
	{		

	}
}
