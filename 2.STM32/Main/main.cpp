#include "sys.h"
#include "led.h"  
#include "delay.h"
#include "usart.h" 
#include "lcd_3.5tft.h"

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	
	delay_init(84);
	uart_init(115200);
	delay_ms(50);
	
	LED_Init();		// LED初始化
	LCD_Init();

	LED1_OFF;
	
	while(1)
	{		

	}
}
