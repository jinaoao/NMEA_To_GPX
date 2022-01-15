/***
	************************************************************************************************
	*	@file  	lcd_3.5tft.c
	*	@version V1.1
	*  @date    2018-12-31
	*	@author  ���ͿƼ�
	*	@brief   3.5��Һ��������������������ILI9488��ʹ��FSMC�ӿ�����
   ************************************************************************************************
   *  @description
	*
	*	V1.1�汾���˵����
	*	
	*	1.�޸� LCD_DrawPoint ����������ɫ����ȷ��BUG
	*
	*	��Ҫ˵����
	*
	*	1. ��Ļ�ֱ��ʽ�Ϊ320*240		
	*	2. ȡģ��ʽΪ����PCtolCD2002Ϊ���������롢��������ʽ��C51��ʽ
	*	3. �ֿ�洢�� lcd_fonts.c �ļ�������������� lcd_fonts.h�ļ�
	*
	*	����˵����
	*	
	*	1. �������ṩ��5����ͬ��С��ASCII�ֿ⣺3216��2412��2010��1608��1206
	*	2. ASCII�ַ���ʾ������ LCD_DisplayString()
	*	3. ������ʾ������LCD_DisplayNumber()����ֱ����ʾ��������
	*
	*	4.	LCD_DrawPoint()	��ָ�����괦���Ƶ�
	*	5.	LCD_DrawLine()		��ָ�����괦����ֱ��
	*	6.	LCD_DrawRect()		��ָ�����괦���ƾ���
	*	7.	LCD_DrawCircle()	��ָ�����괦����Բ��
	*	8.	LCD_DrawEllipse() ��ָ�����괦������Բ
	*	9.	LCD_FillRect()		��ָ�����괦����������
	* 10.	LCD_FillCircle()	��ָ�����괦���Բ������
	*	
	* 11. LCD_SetFont()	  	 �ɸı���ʾ��ASCII�ַ�������
	* 12. LCD_ShowNumMode()	 ��������Ҫ��ʾ�����ֿ��и�λ�Ƿ���ʾ0��ͨ������ʾʱ������ڵ�ʱ�����
	* 13.	LCD_SetColor()     �������û��ʵ���ɫ��������ʾ�ַ�����ͼ��
	* 14.	LCD_SetBackColor() �������ñ�����ɫ�����������Լ���ʾ�ַ�ʱ�ı���ɫ
	* 15.	LCD_DisplayMode()	 �����л�������������ʾ
	*		
	****************************************************************************************************
***/

#include "lcd_3.5tft.h"
#include "delay.h"
#include "usart.h" 

static pFONT *LCD_Fonts;	// ��������ṹ��ָ��

//LCD��ز����ṹ��
struct	
{
	u16 ID;        //������ID	
	u16 Width;		// ˮƽ�ֱ���
	u16 Height;		// ��ֱ�ֱ���
	u32 Color;  		//	LCD��ǰ������ɫ
	u32 BackColor;		//	����ɫ
	u8  Direction;		//	��ʾ����
	u8  ShowNum_Mode;	// �������ģʽ
}LCD;

/*****************************************************************************************
*	�� �� ��: LCD_Delay
*	��ڲ���: a - ��ʱʱ�䣬��λms
*	�� �� ֵ: ��
*	��������: ����ʱ������ʵ��ms������ʱ
*	˵    ��: Ϊ����ֲ�ļ�����Ҷ���ʱ����Ҫ�󲻸ߣ����Բ���Ҫʹ�ö�ʱ������ʱ
******************************************************************************************/

void LCD_Delay(u16 a)
{
	u16 i;
	while(a--)
	{
		for ( i = 0; i < 5000; i++);
	}
}

/*****************************************************************************************
*	�� �� ��: LCD_WR_REG
*	��ڲ���: reg - Ҫ�����ļĴ���
*	�� �� ֵ: ��
*	��������: ѡ��Ҫ�����ļĴ���
*	˵    ��: 
******************************************************************************************/

void LCD_WR_REG(u16 reg)
{   
	*(__IO u16*) FSMC_REG = reg;	 
}

/*****************************************************************************************
*	�� �� ��: LCD_WR_DATA
*	��ڲ���: data - Ҫд�������
*	�� �� ֵ: ��
*	��������: ����Ӧ�ļĴ���д������
*	˵    ��: 
******************************************************************************************/

void LCD_WR_DATA(u16 data)
{	 
	*(__IO u16*) FSMC_DATA = data;	
}
		
/*****************************************************************************************
*	�� �� ��: LCD_RD_DATA
*	��ڲ���: reg - Ҫ��ȡ�ļĴ���
*	�� �� ֵ: �ӸüĴ�����ȡ������ֵ
*	��������: ����Ӧ�ļĴ�����������
*	˵    ��: ��
******************************************************************************************/
u16 LCD_RD_DATA(void)
{
   u16 data;	
	data = *(__IO u16*) FSMC_DATA;	
	return data;	 
}

/*****************************************************************************************
*	�� �� ��: LCD_RD_OnePoint
*	��ڲ���: Ҫ��ȡ�������
*	�� �� ֵ: ��ȡ���������ֵ,������Χ����0
*	��������: ��ȡһ�����ص��RGBֵ(RGB565��ʽ)
*	˵    ��: ���Ͷ�GRAMָ����Ƚ���һ�μٶ���֮��ILI9488�᷵������16λ��ֵ��ǰһ����RG��ֵ��
             ��8λ������һ����B��ֵ��ռ��8λ��
******************************************************************************************/
u16 LCD_RD_OnePoint(u16 x,u16 y)
{
   u16 R_Value = 0, G_Value = 0, B_Value = 0, RGB_Value = 0;
	
	if(x >= LCD.Width||y >= LCD.Height)return 0;
	
   LCD_SetCursor(x,y);                       //Ҫ��ȡ�������
	LCD_WR_REG(0X2E);                         //��GRAMָ��
	R_Value = LCD_RD_DATA();                  //�ٶ�
	R_Value = LCD_RD_DATA();                  //��ȡRG��ֵ
	G_Value = (R_Value&0X00FC)<<3;            //�õ�G��ֵ
	R_Value = R_Value&0XF800;                 //�õ�R��ֵ
	B_Value = (LCD_RD_DATA()&0XF800)>>11;     //��ȡ���õ�B��ֵ
	
	RGB_Value = R_Value | G_Value | B_Value;  //�ϳ�������RGBֵ
	return RGB_Value;
}

/*****************************************************************************************
*	�� �� ��: LCD_GPIO_Config
*	��ڲ���: ��
*	�� �� ֵ: ��
*	��������: ��ʼ��LCD��GPIO
*	˵    ��: ��Ļ��RS������FSMC��A16
******************************************************************************************/

void LCD_GPIO_Config(void)
{ 					
 	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(LCD_CLK,ENABLE);//ʹ��GPIO�ĸ��ù���ʱ��
	
 	/*--------------------- ---��ʼ��FSMC����-----------------------------------*/ 
	
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//�������
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����

	GPIO_InitStructure.GPIO_Pin = LCD_CS_PIN;				 
 	GPIO_Init(LCD_CS_PORT, &GPIO_InitStructure); 
   GPIO_PinAFConfig(LCD_CS_PORT,LCD_CS_PINS,GPIO_AF_FSMC);

	GPIO_InitStructure.GPIO_Pin = LCD_RS_PIN;				 
 	GPIO_Init(LCD_RS_PORT, &GPIO_InitStructure); 
   GPIO_PinAFConfig(LCD_RS_PORT,LCD_RS_PINS,GPIO_AF_FSMC);

	GPIO_InitStructure.GPIO_Pin = LCD_WR_PIN;				 
 	GPIO_Init(LCD_WR_PORT, &GPIO_InitStructure); 
   GPIO_PinAFConfig(LCD_WR_PORT,LCD_WR_PINS,GPIO_AF_FSMC);

	GPIO_InitStructure.GPIO_Pin = LCD_RD_PIN;				 
 	GPIO_Init(LCD_RD_PORT, &GPIO_InitStructure); 
   GPIO_PinAFConfig(LCD_RD_PORT,LCD_RD_PINS,GPIO_AF_FSMC);

	GPIO_InitStructure.GPIO_Pin = LCD_D0_PIN;				 
 	GPIO_Init(LCD_D0_PORT, &GPIO_InitStructure); 
   GPIO_PinAFConfig(LCD_D0_PORT,LCD_D0_PINS,GPIO_AF_FSMC);

	GPIO_InitStructure.GPIO_Pin = LCD_D1_PIN;				 
 	GPIO_Init(LCD_D1_PORT, &GPIO_InitStructure); 
   GPIO_PinAFConfig(LCD_D1_PORT,LCD_D1_PINS,GPIO_AF_FSMC);

	GPIO_InitStructure.GPIO_Pin = LCD_D2_PIN;				 
 	GPIO_Init(LCD_D2_PORT, &GPIO_InitStructure); 
   GPIO_PinAFConfig(LCD_D2_PORT,LCD_D2_PINS,GPIO_AF_FSMC);

	GPIO_InitStructure.GPIO_Pin = LCD_D3_PIN;				 
 	GPIO_Init(LCD_D3_PORT, &GPIO_InitStructure); 
   GPIO_PinAFConfig(LCD_D3_PORT,LCD_D3_PINS,GPIO_AF_FSMC);

	GPIO_InitStructure.GPIO_Pin = LCD_D4_PIN;				 
 	GPIO_Init(LCD_D4_PORT, &GPIO_InitStructure); 
   GPIO_PinAFConfig(LCD_D4_PORT,LCD_D4_PINS,GPIO_AF_FSMC);

	GPIO_InitStructure.GPIO_Pin = LCD_D5_PIN;				 
 	GPIO_Init(LCD_D5_PORT, &GPIO_InitStructure); 
   GPIO_PinAFConfig(LCD_D5_PORT,LCD_D5_PINS,GPIO_AF_FSMC);

	GPIO_InitStructure.GPIO_Pin = LCD_D6_PIN;				 
 	GPIO_Init(LCD_D6_PORT, &GPIO_InitStructure); 
   GPIO_PinAFConfig(LCD_D6_PORT,LCD_D6_PINS,GPIO_AF_FSMC);

	GPIO_InitStructure.GPIO_Pin = LCD_D7_PIN;				 
 	GPIO_Init(LCD_D7_PORT, &GPIO_InitStructure); 
   GPIO_PinAFConfig(LCD_D7_PORT,LCD_D7_PINS,GPIO_AF_FSMC);

	GPIO_InitStructure.GPIO_Pin = LCD_D8_PIN;				 
 	GPIO_Init(LCD_D8_PORT, &GPIO_InitStructure); 
   GPIO_PinAFConfig(LCD_D8_PORT,LCD_D8_PINS,GPIO_AF_FSMC);

	GPIO_InitStructure.GPIO_Pin = LCD_D9_PIN;				 
 	GPIO_Init(LCD_D9_PORT, &GPIO_InitStructure); 
   GPIO_PinAFConfig(LCD_D9_PORT,LCD_D9_PINS,GPIO_AF_FSMC);
	
	GPIO_InitStructure.GPIO_Pin = LCD_D10_PIN;				 
 	GPIO_Init(LCD_D10_PORT, &GPIO_InitStructure); 
   GPIO_PinAFConfig(LCD_D10_PORT,LCD_D10_PINS,GPIO_AF_FSMC);

	GPIO_InitStructure.GPIO_Pin = LCD_D11_PIN;				 
 	GPIO_Init(LCD_D11_PORT, &GPIO_InitStructure); 
	GPIO_PinAFConfig(LCD_D11_PORT,LCD_D11_PINS,GPIO_AF_FSMC);
	
	GPIO_InitStructure.GPIO_Pin = LCD_D12_PIN;				 
 	GPIO_Init(LCD_D12_PORT, &GPIO_InitStructure); 
   GPIO_PinAFConfig(LCD_D12_PORT,LCD_D12_PINS,GPIO_AF_FSMC);

	GPIO_InitStructure.GPIO_Pin = LCD_D13_PIN;				 
 	GPIO_Init(LCD_D13_PORT, &GPIO_InitStructure); 
   GPIO_PinAFConfig(LCD_D13_PORT,LCD_D13_PINS,GPIO_AF_FSMC);

	GPIO_InitStructure.GPIO_Pin = LCD_D14_PIN;				 
 	GPIO_Init(LCD_D14_PORT, &GPIO_InitStructure); 
   GPIO_PinAFConfig(LCD_D14_PORT,LCD_D14_PINS,GPIO_AF_FSMC);

	GPIO_InitStructure.GPIO_Pin = LCD_D15_PIN;				 
 	GPIO_Init(LCD_D15_PORT, &GPIO_InitStructure); 
   GPIO_PinAFConfig(LCD_D15_PORT,LCD_D15_PINS,GPIO_AF_FSMC);
	
 	/*-------------------------��ʼ��������������--------------------------------*/ 

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;//2MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	
	//��ʼ����λ����
 	GPIO_InitStructure.GPIO_Pin = LCD_RST_PIN;				
 	GPIO_Init(LCD_RST_PORT, &GPIO_InitStructure);	
	
	//��ʼ����������
 	GPIO_InitStructure.GPIO_Pin = LCD_BL_PIN;			 
 	GPIO_Init(LCD_BL_PORT, &GPIO_InitStructure);		
	GPIO_SetBits(LCD_BL_PORT,LCD_BL_PIN);			//����LCD����	
}  

/*****************************************************************************************
*	�� �� ��: LCD_FSMC_Config
*	��ڲ���: ��
*	�� �� ֵ: ��
*	��������: ��ʼ��FSMC����
*	˵    ��: ʹ��BANK1
******************************************************************************************/

void	LCD_FSMC_Config(void)
{
	FSMC_NORSRAMTimingInitTypeDef  SET;	
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;	
	
   RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC,ENABLE);	//ʹ��FSMCʱ��
	
	SET.FSMC_AddressSetupTime = 0x00;	 		//��ַ����ʱ��
	SET.FSMC_AddressHoldTime = 0x00;		 		//��ַ����ʱ��
	SET.FSMC_DataSetupTime = 0x03;		 		//���ݱ���ʱ��
	SET.FSMC_BusTurnAroundDuration = 0x00;
	SET.FSMC_CLKDivision = 0x00;
	SET.FSMC_DataLatency = 0x00;
	SET.FSMC_AccessMode = FSMC_AccessMode_A;	 //ģʽA 

	FSMC_NORSRAMInitStructure.FSMC_Bank 				  = FSMC_Bank1_NORSRAM1;			
	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux 	  = FSMC_DataAddressMux_Disable; 
	FSMC_NORSRAMInitStructure.FSMC_MemoryType 		  = FSMC_MemoryType_SRAM;			
	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth 	  = FSMC_MemoryDataWidth_16b;		
	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode 	  = FSMC_BurstAccessMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait	  = FSMC_AsynchronousWait_Disable; 
	FSMC_NORSRAMInitStructure.FSMC_WrapMode 			  = FSMC_WrapMode_Disable;   
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive   = FSMC_WaitSignalActive_BeforeWaitState;  
	FSMC_NORSRAMInitStructure.FSMC_WriteOperation 	  = FSMC_WriteOperation_Enable;					
	FSMC_NORSRAMInitStructure.FSMC_WaitSignal 		  = FSMC_WaitSignal_Disable;   
	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode		  = FSMC_ExtendedMode_Enable; 	
	FSMC_NORSRAMInitStructure.FSMC_WriteBurst 		  = FSMC_WriteBurst_Disable; 
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct  = &SET;  

	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  //��ʼ��FSMC
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);  // ʹ��BANK1  
}
	
/*****************************************************************************************
*	�� �� ��: LCD_Init
*	��ڲ���: ��
*	�� �� ֵ: ��
*	��������: ��ʼ��LCD������
*	˵    ��: ��Ҫ�ǲ���ILI9488����ؼĴ��������б�Ҫ�����ã�Ĭ��������ʾ
******************************************************************************************/

void LCD_Init(void)
{
	LCD_GPIO_Config();	// ��ʼ��GPIO
	LCD_FSMC_Config();	// ��ʼ��FSMC����
	
  // ��λILI9488
	GPIO_ResetBits(LCD_RST_PORT,LCD_RST_PIN);	LCD_Delay(30); 	
	GPIO_SetBits(LCD_RST_PORT,LCD_RST_PIN);	LCD_Delay(30);

	//��ȡLCD��������ID��
	LCD_WR_REG(0XD3);	
   LCD.ID=LCD_RD_DATA();     //�ٶ�
	LCD.ID=LCD_RD_DATA();     //��0x00
	LCD.ID=LCD_RD_DATA();     //��0x94
	LCD.ID<<=8;               //0x94�����8λ
	LCD.ID|=LCD_RD_DATA();    //��0x88����ȡ����ID��
	printf(" LCD ID:ILI%x\r\n",LCD.ID);
	if(LCD.ID!=0x9488)while(1);	
	
   // ��ʼ��ILI9341
	LCD_WR_REG(0xE0); //P-Gamma
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x03);
	LCD_WR_DATA(0x0C);
	LCD_WR_DATA(0x09);
	LCD_WR_DATA(0x17);
	LCD_WR_DATA(0x09);
	LCD_WR_DATA(0x3E);
	LCD_WR_DATA(0x89);
	LCD_WR_DATA(0x49);
	LCD_WR_DATA(0x08);
	LCD_WR_DATA(0x0D);
	LCD_WR_DATA(0x0A);
	LCD_WR_DATA(0x13);
	LCD_WR_DATA(0x15);
	LCD_WR_DATA(0x0F);
	LCD_WR_REG(0XE1); //N-Gamma
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x11);
	LCD_WR_DATA(0x15);
	LCD_WR_DATA(0x03);
	LCD_WR_DATA(0x0F);
	LCD_WR_DATA(0x05);
	LCD_WR_DATA(0x2D);
	LCD_WR_DATA(0x34);
	LCD_WR_DATA(0x41);
	LCD_WR_DATA(0x02);
	LCD_WR_DATA(0x0B);
	LCD_WR_DATA(0x0A);
	LCD_WR_DATA(0x33);
	LCD_WR_DATA(0x37);
	LCD_WR_DATA(0x0F);

	LCD_WR_REG(0XC0); //Power Control 1
	LCD_WR_DATA(0x17); //Vreg1out
	LCD_WR_DATA(0x15); //Verg2out
	LCD_WR_REG(0xC1); //Power Control 2
	LCD_WR_DATA(0x41); //VGH,VGL
	LCD_WR_REG(0xC5); //Power Control 3
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x12); //Vcom
	LCD_WR_DATA(0x80);

	LCD_WR_REG(0x36); //Memory Access
	LCD_WR_DATA(0x48);
	LCD_WR_REG(0x3A); // Interface Pixel Format
	LCD_WR_DATA(0x55);
	LCD_WR_REG(0XB0); // Interface Mode Control
	LCD_WR_DATA(0x00);
	LCD_WR_REG(0xB1); //Frame rate
	LCD_WR_DATA(0xA0); //60Hz
	LCD_WR_REG(0xB4); //Display Inversion Control
	LCD_WR_DATA(0x02); //2-dot
	LCD_WR_REG(0XB6); //RGB/MCU Interface Control
	LCD_WR_DATA(0x02); //MCU
	LCD_WR_DATA(0x02); //Source,Gate scan dieection
	LCD_WR_REG(0XE9); // Set Image Function
	LCD_WR_DATA(0x00); // Disable 24 bit data input
	LCD_WR_REG(0xF7);// Adjust Control
	LCD_WR_DATA(0xA9);
	LCD_WR_DATA(0x51);
	LCD_WR_DATA(0x2C);
	LCD_WR_DATA(0x82);
	// D7 stream, loose
	LCD_WR_REG(0x11); //Sleep out
	delay_ms(120);
	LCD_WR_REG(0x29); //Display on
	
	LCD_SetBackColor(LCD_BLACK); 	// ���ñ���ɫ
	LCD_SetColor(LCD_WHITE);		// ���û�����ɫ
	LCD_SetFont(&Font24);  			// ����Ĭ������
	LCD_ShowNumMode(Fill_Space);	// �����������ģʽ
	LCD_DisplayMode(Mode_H);		// ������ʾ��������
	LCD_Clear();		// ����
}

/*****************************************************************************************
*	�� �� ��:	 LCD_SetCursor
*	��ڲ���:	 x - ˮƽ����
*			  	 y - ��ֱ����
*	�� �� ֵ: ��
*	��������: ������ĻҪ��ʾ���ݵ�����
*	˵    ��: 0x2A Ϊˮƽ����Ĵ�����ַ��0x2BΪ��ֱ����Ĵ�����ַ
******************************************************************************************/

void LCD_SetCursor(u16 x, u16 y)
{	   
   //ILI9488��������ʱ�����END����Ҳд��ȥ����ΪEND����ͨ����ȷ��������ֱ��д�������
	LCD_WR_REG(0x2A); 							
	LCD_WR_DATA(x>>8);LCD_WR_DATA(x&0XFF); 	//����ˮƽ���꣬��λ��ǰ	
	LCD_WR_DATA(0x01);   // �������X����Ϊ480
	LCD_WR_DATA(0xDF); 	
	LCD_WR_REG(0x2B); 						
	LCD_WR_DATA(y>>8);LCD_WR_DATA(y&0XFF); 	//���ô�ֱ���꣬��λ��ǰ	
	LCD_WR_DATA(0x01);   // �������Y����Ϊ480
	LCD_WR_DATA(0xDF); 
} 

/*****************************************************************************************
*	�� �� ��:	 LCD_SetColor
*	��ڲ���:	 Color - Ҫ���õ���ɫ
*	�� �� ֵ: ��
*	��������: ���û��ʵ���ɫ��������ʾ�ַ�������ͼ�ε�
*	˵    ��: ��Ȼ����3.5�����Ļʹ�õ���ɫ��ʽ��16λ��RGB565����������Ϊ�˷����û�ʹ�ã�
*				 ��ڲ���ʹ�õ���24λ��RGB888��ɫ��Ȼ����ͨ������ת����16λɫ���û����Ժܷ���
*				 ���ڵ�����ȡɫ����ȡ24λ����ɫ���ٽ���24λ��ɫֵ����ú������ɡ�		 
******************************************************************************************/

void LCD_SetColor(u32 Color)
{
	u16 Red_Value = 0, Green_Value = 0, Blue_Value = 0; //������ɫͨ����ֵ
	
	Red_Value   = (u16)((Color&0xF80000)>>8);		// ��ȡ��ɫ��ֵ
	Green_Value = (u16)((Color&0x00FC00)>>5);		// ��ȡ��ɫ��ֵ
	Blue_Value  = (u16)((Color&0x0000F8)>>3);		// ��ȡ��ɫ��ֵ
	
	LCD.Color = (u16)(Red_Value | Green_Value | Blue_Value);		// �ϳ�16λɫ����ɫ��ʽRGB565
}

/*****************************************************************************************
*	�� �� ��:	 LCD_SetBackColor
*	��ڲ���:	 Color - Ҫ���õ���ɫ
*	�� �� ֵ: ��
*	��������: �����������������ʾ������ɫ
*	˵    ��: ��Ȼ����3.5�����Ļʹ�õ���ɫ��ʽ��16λ��RGB565����������Ϊ�˷����û�ʹ�ã�
*				 ��ڲ���ʹ�õ���24λ��RGB888��ɫ��Ȼ����ͨ������ת����16λɫ���û����Ժܷ���
*				 ���ڵ�����ȡɫ����ȡ24λ����ɫ���ٽ���24λ��ɫֵ����ú������ɡ�		 
******************************************************************************************/

void LCD_SetBackColor(u32 Color)
{
	u16 Red_Value = 0, Green_Value = 0, Blue_Value = 0; //������ɫͨ����ֵ
	
	Red_Value   = (u16)((Color&0xF80000)>>8);	// ��ȡ��ɫ��ֵ
	Green_Value = (u16)((Color&0x00FC00)>>5); // ��ȡ��ɫ��ֵ
	Blue_Value  = (u16)((Color&0x0000F8)>>3); // ��ȡ��ɫ��ֵ
	
	LCD.BackColor = (u16)(Red_Value | Green_Value | Blue_Value);	// �ϳ�16λɫ����ɫ��ʽRGB565
}

/*****************************************************************************************
*	�� �� ��:	 LCD_DisplayMode
*	��ڲ���:	 direction - ������������ʾ����ѡ���� Mode_H ������Mode_V ��ֱ
*	�� �� ֵ: ��
*	��������: ����Һ��������ʾ���򣬺���������
*	˵    ��: ��	 
******************************************************************************************/

void LCD_DisplayMode(u8 direction)
{
	LCD.Direction = direction;		// �޸�ȫ�ֱ����������־λ
	
	if (LCD.Direction == Mode_H) 		// ������ʾ
	{
		LCD_WR_REG(0X36);		// ɨ�跽�����üĴ���
		LCD_WR_DATA(0X28); 	//	ɨ�跽�򣬴��ϵ���	�����ҵ���
		
		LCD_WR_REG(0x2A); 	
		LCD_WR_DATA(0x00);	// ����x���꣨������û�����ã�ֻ����Ҫ��д����ѣ�
		LCD_WR_DATA(0x00); 			
		LCD_WR_DATA(0x01);	// �������x����Ϊ320
		LCD_WR_DATA(0XDF); 
			
		LCD_WR_REG(0x2B); 
		LCD_WR_DATA(0x00);	// ����y���꣨������û�����ã�ֻ����Ҫ��д����ѣ�
		LCD_WR_DATA(0x00); 		
		LCD_WR_DATA(0x01);	// �������y����Ϊ240
		LCD_WR_DATA(0x3F); 		
		
		LCD.Width  = 480;		// ˮƽ���320
		LCD.Height = 320;		// ��ֱ���240
	}
	else if(LCD.Direction == Mode_V)	// ������ʾ
	{
		LCD_WR_REG(0X36);		// ɨ�跽�����üĴ���
		LCD_WR_DATA(0X48); 	//	ɨ�跽�򣬴����ң����ϵ���	
		
		LCD_WR_REG(0x2A); 	
		LCD_WR_DATA(0x00);	// ����x���꣨������û�����ã�ֻ����Ҫ��д����ѣ�
		LCD_WR_DATA(0x00); 			
		LCD_WR_DATA(0x01);   // �������x����Ϊ240
		LCD_WR_DATA(0x3F); 				
                           
		LCD_WR_REG(0x2B);    
		LCD_WR_DATA(0x00);   // ����y���꣨������û�����ã�ֻ����Ҫ��д����ѣ�
		LCD_WR_DATA(0x00); 			
		LCD_WR_DATA(0x01);   // �������y����Ϊ320
		LCD_WR_DATA(0XDF); 			
		                     
		LCD.Width  = 320;    // ˮƽ���240
		LCD.Height = 480;		// ��ֱ���320
	}
}

/*****************************************************************************************
*	�� �� ��:	 LCD_Clear
*	��ڲ���: ��
*	�� �� ֵ: ��
*	��������: ���������Ļ����ʾ
*	˵    ��: �������ɫΪ����ɫ����LCD_SetBackColor����
******************************************************************************************/

void LCD_Clear(void)
{ 
	u32 i = 0;
	
	LCD_SetCursor(0,0);	// ������ʼ����
	LCD_WR_REG(0X2C);		// ��ʼд��GRAM

	for(i=0;i<320*480;i++)	// �ܹ���Ҫд��320*240���㣬ILI9341�������Ļ�ķֱ����Զ�������ʾ
	{
		*(__IO u16*) FSMC_DATA = LCD.BackColor;	// д�뱳��ɫ
	}
}

/*****************************************************************************************
*	�� �� ��:	 LCD_DrawPoint
*	��ڲ���:	 x - ˮƽ����
*			  	 y - ��ֱ����
*				 color - Ҫ��ʾ����ɫ
*	�� �� ֵ: ��
*	��������: ���ƶ����괦����ָ����ɫ�ĵ�
*	˵    ��: ��
******************************************************************************************/

void LCD_DrawPoint(u16 x,u16 y)
{
	LCD_SetCursor(x,y);	// ��������
	LCD_WR_REG(0X2C);		// д��GRAM
	*(__IO u16*) FSMC_DATA = LCD.Color; 	// д����ɫ
}

/*****************************************************************************************
*	�� �� ��:	 LCD_SetFont
*	��ڲ���:	 *fonts - ��Ӧ����ṹ��ָ��ĵ�ַ
*	�� �� ֵ: ��
*	��������: ��������
*	˵    ��: ��Ҫ����ȡģ������ѡ��Font32/Font24/Font20/Font16/Font12
******************************************************************************************/

void LCD_SetFont(pFONT *fonts)
{
	LCD_Fonts = fonts;
}

/*****************************************************************************************
*	�� �� ��:	 LCD_DisplayChar
*	��ڲ���:	 x - ˮƽ����
*			  	 y - ��ֱ����
*				 c - �ַ���ASCIIֵ
*	�� �� ֵ: ��
*	��������: ��ָ�����괦��ʾ����ASCII�ַ�
*	˵    ��: ��ͨ�� LCD_SetFont() ����������Ӧ������
******************************************************************************************/

void LCD_DisplayChar(u16 x, u16 y,u8 add)
{
	u16  index = 0, counter = 0;
   u8   disChar;	//��ģ��ֵ
	u16  Xaddress = x; //ˮƽ����
	
	add = add - 32; 
	for(index = 0; index < LCD_Fonts->Sizes; index++)
	{
		disChar = LCD_Fonts->table[add*LCD_Fonts->Sizes + index]; //��ȡ�ַ���ģֵ
		for(counter = 0; counter < 8; counter++)
		{ 
			if(disChar & 0x01)	
			{				
				LCD_SetCursor(Xaddress,y);	// ��������
				LCD_WR_REG(0X2C);		// д��GRAM
				*(__IO u16*) FSMC_DATA = LCD.Color; 	//��ǰģֵ��Ϊ0ʱ��ʹ�û���ɫ���
			}
			else		
			{		
				LCD_SetCursor(Xaddress,y);	// ��������
				LCD_WR_REG(0X2C);		// д��GRAM
				*(__IO u16*) FSMC_DATA = LCD.BackColor; 	//����ʹ�ñ���ɫ���Ƶ�
			}
			disChar >>= 1;
			Xaddress++;  //ˮƽ�����Լ�
			
			if( (Xaddress - x)==LCD_Fonts->Width ) //���ˮƽ����ﵽ���ַ���ȣ����˳���ǰѭ��
			{													//������һ�еĻ���
				Xaddress = x;
				y++;
				break;
			}
		}	
	}	
}

/*****************************************************************************************
*	�� �� ��:	 LCD_DisplayString
*	��ڲ���:	 x - ˮƽ����
*			  	 y - ��ֱ����
*				 *p - Ҫ��ʾ���ַ���
*	�� �� ֵ: ��
*	��������: ��ָ�����괦��ʾ�ַ���
*	˵    ��: ��ͨ�� LCD_SetFont() ����������Ӧ������
******************************************************************************************/

void LCD_DisplayString( u16 x, u16 y, u8 *p) 
{  
	while( (x<LCD.Width)&&(*p != 0) )	//�ж���ʾ�����Ƿ񳬳���ʾ�������ַ��Ƿ�Ϊ���ַ�
	{
		 LCD_DisplayChar( x,y,*p);
		 x += LCD_Fonts->Width; //��ʾ��һ���ַ�
		 p++;	//ȡ��һ���ַ���ַ
	}
}

/*****************************************************************************************
*	�� �� ��:	 GetNumber
*	��ڲ���:	 number - Ŀ������
*			  	 size - Ŀ�����ĳ���
*	�� �� ֵ: ȡ�����ĵ�Nλ���������ڲ�������Խ�����ʾ
*	��������: ȡ���ĵ�Nλ����
*	˵    ��: �� LCD_DisplayNumber()�ﱻ����
******************************************************************************************/

u8 GetNumber(u32 num,u8 size)
{
	u32 numPow = 1;
	u8  vaule;
	
	while(size>0)
	{
		numPow *=10;
		size--;
	}
	vaule = (num/numPow)%10;
	return vaule;	
}

/*****************************************************************************************
*	�� �� ��:	 LCD_ShowNumMode
*	��ڲ���:	 mode - �������ģʽ��Fill_Space ���ո�Fill_Zero �����
*	�� �� ֵ: ��
*	��������: ����������ʾ�����ģʽ
*	˵    ��: ʹ�� LCD_DisplayNumber() ��ʾ����ʱ�����ô˺������ø�λ�����ģʽ��
*				 ͨ������ʾʱ������ڵ�ʱ�����
******************************************************************************************/

void LCD_ShowNumMode(u8 mode)
{
	LCD.ShowNum_Mode = mode;
}

/*****************************************************************************************
*	�� �� ��:	 LCD_DisplayNumber
*	��ڲ���:	 x - ˮƽ����
*			  	 y - ��ֱ����
*				 number - Ҫ��ʾ������
*				 len - ���ֵĳ���
*	�� �� ֵ: ��
*	��������: ��ʾ��������
*	˵    ��: ��Ҫָ����ʾ��λ��
******************************************************************************************/

void LCD_DisplayNumber( u16 x, u16 y, u32 number, u8 len) 
{  
	u8 i,value;
	u8 zero_Flag = 0;

	for(i=0;i<len;i++)
	{
		value = GetNumber(number,len-i-1);	//��ȡ��ǰ�����ĵ�Nλ��
		if( zero_Flag==0 && (i<len-1) )	//�ж�ǰ��Ϊ0�Ĳ���
		{
			if(value == 0)
			{
				if(LCD.ShowNum_Mode == 0)	
					LCD_DisplayChar( x+i*LCD_Fonts->Width, y,48);	//���0
				else
					LCD_DisplayChar( x+i*LCD_Fonts->Width, y,32);	//���ո�
				continue;
			}
			else
				zero_Flag = 1;	//��������һ����0��ʱ��1
		}									
		LCD_DisplayChar( x+i*LCD_Fonts->Width, y, value+48 );	//����ֵ���������ʾ
	}
}

/*****************************************************************************************
*	�� �� ��:	 LCD_DrawLine
*	��ڲ���:	 x1��y1 - �������
*			  	 x2��y2 - �յ�����
*	�� �� ֵ: ��
*	��������: ����ֱ��
*	˵    ��: ��
******************************************************************************************/

#define ABS(X)  ((X) > 0 ? (X) : -(X))    

void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
{
	int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0, 
	yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0, 
	curpixel = 0;

	deltax = ABS(x2 - x1);        /* The difference between the x's */
	deltay = ABS(y2 - y1);        /* The difference between the y's */
	x = x1;                       /* Start x off at the first pixel */
	y = y1;                       /* Start y off at the first pixel */

	if (x2 >= x1)                 /* The x-values are increasing */
	{
	 xinc1 = 1;
	 xinc2 = 1;
	}
	else                          /* The x-values are decreasing */
	{
	 xinc1 = -1;
	 xinc2 = -1;
	}

	if (y2 >= y1)                 /* The y-values are increasing */
	{
	 yinc1 = 1;
	 yinc2 = 1;
	}
	else                          /* The y-values are decreasing */
	{
	 yinc1 = -1;
	 yinc2 = -1;
	}

	if (deltax >= deltay)         /* There is at least one x-value for every y-value */
	{
	 xinc1 = 0;                  /* Don't change the x when numerator >= denominator */
	 yinc2 = 0;                  /* Don't change the y for every iteration */
	 den = deltax;
	 num = deltax / 2;
	 numadd = deltay;
	 numpixels = deltax;         /* There are more x-values than y-values */
	}
	else                          /* There is at least one y-value for every x-value */
	{
	 xinc2 = 0;                  /* Don't change the x for every iteration */
	 yinc1 = 0;                  /* Don't change the y when numerator >= denominator */
	 den = deltay;
	 num = deltay / 2;
	 numadd = deltax;
	 numpixels = deltay;         /* There are more y-values than x-values */
	}
	for (curpixel = 0; curpixel <= numpixels; curpixel++)
	{
	 LCD_DrawPoint(x,y);             /* Draw the current pixel */
	 num += numadd;              /* Increase the numerator by the top of the fraction */
	 if (num >= den)             /* Check if numerator >= denominator */
	 {
		num -= den;               /* Calculate the new numerator value */
		x += xinc1;               /* Change the x as appropriate */
		y += yinc1;               /* Change the y as appropriate */
	 }
	 x += xinc2;                 /* Change the x as appropriate */
	 y += yinc2;                 /* Change the y as appropriate */
	}
}

/*****************************************************************************************
*	�� �� ��:	 LCD_DrawRect
*	��ڲ���:	 x��y - �������
*			  	 width - ���γ���
*				 height - ���ο��
*	�� �� ֵ: ��
*	��������: ���ƾ��ο�
*	˵    ��: ��
******************************************************************************************/

void LCD_DrawRect(u16 x, u16 y, u16 width, u16 height)
{
	/* draw horizontal lines */
	LCD_DrawLine(x, y, x+width, y);
	LCD_DrawLine(x, y+height, x+width, y+height);

	/* draw vertical lines */
	LCD_DrawLine(x, y, x, y+height);
	LCD_DrawLine(x+width, y, x+width, y+height);
}

/*****************************************************************************************
*	�� �� ��:	 LCD_DrawCircle
*	��ڲ���:	 x��y - �������
*			  	 r - �뾶
*	�� �� ֵ: ��
*	��������: ����Բ�ο�
*	˵    ��: �뾶���ܴ���xy�����ֵ
******************************************************************************************/

void LCD_DrawCircle(u16 x, u16 y, u16 r)
{
	int Xadd = -r, Yadd = 0, err = 2-2*r, e2;
	do {   

		LCD_DrawPoint(x-Xadd,y+Yadd);
		LCD_DrawPoint(x+Xadd,y+Yadd);
		LCD_DrawPoint(x+Xadd,y-Yadd);
		LCD_DrawPoint(x-Xadd,y-Yadd);
		
		e2 = err;
		if (e2 <= Yadd) {
			err += ++Yadd*2+1;
			if (-Xadd == Yadd && e2 <= Xadd) e2 = 0;
		}
		if (e2 > Xadd) err += ++Xadd*2+1;
    }
    while (Xadd <= 0); 
}

/*****************************************************************************************
*	�� �� ��:	 LCD_DrawEllipse
*	��ڲ���:	 x��y - ��������
*			  	 r1��r2 - �ֱ�Ϊˮƽ�ʹ�ֱ����ĳ���
*	�� �� ֵ: ��
*	��������: ������Բ��
*	˵    ��: ��
******************************************************************************************/

void LCD_DrawEllipse(int x, int y, int r1, int r2)
{
  int Xadd = -r1, Yadd = 0, err = 2-2*r1, e2;
  float K = 0, rad1 = 0, rad2 = 0;
   
  rad1 = r1;
  rad2 = r2;
  
  if (r1 > r2)
  { 
    do {
      K = (float)(rad1/rad2);
		 
		LCD_DrawPoint(x-Xadd,y+(u16)(Yadd/K));
		LCD_DrawPoint(x+Xadd,y+(u16)(Yadd/K));
		LCD_DrawPoint(x+Xadd,y-(u16)(Yadd/K));
		LCD_DrawPoint(x-Xadd,y-(u16)(Yadd/K));     
		 
      e2 = err;
      if (e2 <= Yadd) {
        err += ++Yadd*2+1;
        if (-Xadd == Yadd && e2 <= Xadd) e2 = 0;
      }
      if (e2 > Xadd) err += ++Xadd*2+1;
    }
    while (Xadd <= 0);
  }
  else
  {
    Yadd = -r2; 
    Xadd = 0;
    do { 
      K = (float)(rad2/rad1);

		LCD_DrawPoint(x-(u16)(Xadd/K),y+Yadd);
		LCD_DrawPoint(x+(u16)(Xadd/K),y+Yadd);
		LCD_DrawPoint(x+(u16)(Xadd/K),y-Yadd);
		LCD_DrawPoint(x-(u16)(Xadd/K),y-Yadd);  
		 
      e2 = err;
      if (e2 <= Xadd) {
        err += ++Xadd*3+1;
        if (-Yadd == Xadd && e2 <= Yadd) e2 = 0;
      }
      if (e2 > Yadd) err += ++Yadd*3+1;     
    }
    while (Yadd <= 0);
  }
}

/*****************************************************************************************
*	�� �� ��:	 LCD_FillRect
*	��ڲ���:	 x��y - ��������
*				 width - ����
*				 height - ���	
*	�� �� ֵ: ��
*	��������: ����������
*	˵    ��: ��
******************************************************************************************/

void LCD_FillRect(u16 x, u16 y, u16 width, u16 height)
{
	u16 i = 0,j = 0;

	for(i=0;i<height;i++)
	{
		LCD_SetCursor(x,y+i);   // ���ù��λ�� 
		LCD_WR_REG(0X2C);			// ��ʼд��GRAM
		for(j=0;j<width;j++)
		{
			*(__IO u16*) FSMC_DATA = LCD.Color;	//д������ 
		}
	}
}

/*****************************************************************************************
*	�� �� ��:	 LCD_FillCircle
*	��ڲ���:	 x��y - ��������
*				 r - �뾶
*	�� �� ֵ: ��
*	��������: ���Բ������
*	˵    ��: ��
******************************************************************************************/

void LCD_FillCircle(u16 x, u16 y, u16 r)
{
  int32_t  D;    /* Decision Variable */ 
  uint32_t  CurX;/* Current X Value */
  uint32_t  CurY;/* Current Y Value */ 
  
  D = 3 - (r << 1);
  
  CurX = 0;
  CurY = r;
  
  while (CurX <= CurY)
  {
    if(CurY > 0) 
    { 
		LCD_DrawLine(x - CurX, y - CurY,x - CurX,y - CurY + 2*CurY);
		LCD_DrawLine(x + CurX, y - CurY,x + CurX,y - CurY + 2*CurY); 
    }
    
    if(CurX > 0) 
    {
		LCD_DrawLine(x - CurY, y - CurX,x - CurY,y - CurX + 2*CurX);
		LCD_DrawLine(x + CurY, y - CurX,x + CurY,y - CurX + 2*CurX); 		 
    }
    if (D < 0)
    { 
      D += (CurX << 2) + 6;
    }
    else
    {
      D += ((CurX - CurY) << 2) + 10;
      CurY--;
    }
    CurX++;
  }
  
  LCD_DrawCircle(x, y, r);  
}

/*****************************************************************************************
*	�� �� ��:	 LCD_Color_Fill
*	��ڲ���:	 x1��y1 - �������
*						 x2��y2 - �յ�����
*	�� �� ֵ: ��
*	��������: ��ָ�����������ָ����ɫ��	
*	˵    ��: ��
******************************************************************************************/

void LCD_Color_Fill(u16 x1, u16 y1, u16 x2, u16 y2, u16 *color)
{
	u16 i,j;
	u16 height,width;
	
	width = x2-x1+1;
	height = y2-y1+1;
	
	for(i=0;i<height;i++)
	{
		LCD_SetCursor(x1,y1+i);   // ���ù��λ�� 
		LCD_WR_REG(0X2C);			// ��ʼд��GRAM
		for(j=0;j<width;j++)
		{
			*(__IO u16*) FSMC_DATA = color[i*width+j];	//д������ 
		}
	}
}

