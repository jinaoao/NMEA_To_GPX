/***
	***************************************************************************
	*	@file  	key.c
	*	@version V1.0.0
	*	@brief   按键接口相关函数
   ***************************************************************************
   *  @description
	*
	*  初始化按键引脚，配置为上拉输入、速度等级2M。
	* 	
	***************************************************************************
***/

#include "key.h"  

// 函数：按键IO口初始化
//
void KEY_Init(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure; //定义结构体
	RCC_AHB1PeriphClockCmd ( KEY_CLK, ENABLE); 	//初始化KEY时钟	
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;   //输出模式
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;	//上拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; //速度选择
	GPIO_InitStructure.GPIO_Pin   = KEY_PIN;	 
	
	GPIO_Init(KEY_PORT, &GPIO_InitStructure);	

}

// 函数：按键扫描
//	返回：KEY_ON - 按键按下，KEY_OFF - 按键放开 
//			
u8	KEY_Scan(void)
{
	if( GPIO_ReadInputDataBit ( KEY_PORT,KEY_PIN) == 0 )	//检测按键是否被按下
	{	
		delay_ms(10);	//延时消抖
		if(GPIO_ReadInputDataBit ( KEY_PORT,KEY_PIN) == 0)	//再次检测是否为低电平
		{
			while(GPIO_ReadInputDataBit ( KEY_PORT,KEY_PIN) == 0);	//等待按键放开
			return KEY_ON;	//返回按键按下标志
		}
	}
	return KEY_OFF;	
}


