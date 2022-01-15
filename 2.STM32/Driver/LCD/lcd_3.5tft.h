#ifndef __LCD_H
#define __LCD_H		

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

#include "sys.h"
#include "lcd_fonts.h"
#include "stdint.h"
#include "stdio.h"

/*--------------------------------------- ������ɫ ----------------------------------*/
//	 ��Ȼ����3.5�����Ļʹ�õ���ɫ��ʽ��16λ��RGB565����������Ϊ�˷����û�ʹ�ã�
//	 ��ڲ���ʹ�õ���24λ��RGB888��ɫ��Ȼ����ͨ�������Զ�ת����16λɫ���û����Ժܷ���
//	 ���ڵ�����ȡɫ����ȡ24λ����ɫ���ٽ���24λ��ɫ����LCD_SetColor()��LCD_SetBackColor()
//  �Ϳ���Ҫ��ʾ����Ӧ����ɫ��

#define 	LCD_WHITE       0xFFFFFF	// ��ɫ
#define 	LCD_BLACK       0x000000	// ��ɫ
                           
#define 	LCD_BLUE        0x0000FF	// ��ɫ
#define 	LCD_GREEN       0x00FF00   // ��ɫ
#define 	LCD_RED         0xFF0000   // ��ɫ
#define 	LCD_CYAN        0x00FFFF   // ����ɫ
#define 	LCD_MAGENTA     0xFF00FF   // ��ɫ
#define 	LCD_YELLOW      0xFFFF00   // ��ɫ
#define 	LCD_GREY        0x2C2C2C   // ��ɫ
                                    
#define 	LIGHT_BLUE      0x8080FF   // ����ɫ
#define 	LIGHT_GREEN     0x80FF80   // ����ɫ
#define 	LIGHT_RED       0xFF8080   // ����ɫ
#define 	LIGHT_CYAN      0x80FFFF   // ������ɫ
#define 	LIGHT_MAGENTA   0xFF80FF   // ����ɫ
#define 	LIGHT_YELLOW    0xFFFF80   // ����ɫ
#define 	LIGHT_GREY      0xA3A3A3   // ����ɫ
                                     
#define 	DARK_BLUE       0x000080   // ����ɫ
#define 	DARK_GREEN      0x008000   // ����ɫ
#define 	DARK_RED        0x800000   // ����ɫ
#define 	DARK_CYAN       0x008080   // ������ɫ
#define 	DARK_MAGENTA    0x800080   // ����ɫ
#define 	DARK_YELLOW     0x808000   // ����ɫ
#define 	DARK_GREY       0x404040   // ����ɫ

/*------------------------------------- �������� -------------------------------------*/

void 	LCD_Init(void);	// ��ʼ��LCD
void 	LCD_Clear(void);	// ����

void 	LCD_SetColor(u32 Color);			// ���û�����ɫ
void 	LCD_SetBackColor(u32 Color);		// ���ñ���ɫ
void 	LCD_SetFont(pFONT *fonts);			// ��������
void 	LCD_SetCursor(u16 x, u16 y);		// ��������
void 	LCD_DisplayMode(u8 direction);   // ������ʾ����

void 	LCD_DisplayChar(u16 x, u16 y,u8 add);							// ��ָ�����괦��ʾ����ASCII�ַ�
void 	LCD_DisplayString( u16 x, u16 y, u8 *p);						// ��ָ�����괦��ʾ�ַ���
void 	LCD_ShowNumMode(u8 mode);											// ����������ʾ�����ģʽ
void 	LCD_DisplayNumber( u16 x, u16 y, u32 number, u8 len) ;   // ��ʾʮ������

void	LCD_DrawPoint(u16 x,u16 y);					// ����
void  LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);		// ����
void  LCD_DrawRect(u16 x, u16 y, u16 width, u16 height);	// ������
void  LCD_DrawCircle(u16 x, u16 y, u16 r);					// ��Բ
void  LCD_DrawEllipse(int x, int y, int r1, int r2);		// ����Բ

void  LCD_FillRect(u16 x, u16 y, u16 width, u16 height);		// ������
void  LCD_FillCircle(u16 x, u16 y, u16 r);						// ���Բ
void LCD_Color_Fill(u16 x1, u16 y1, u16 x2, u16 y2, u16 *color); //��ָ�����������ָ����ɫ��	

/*-------------------------------LCD��ز����궨��-------------------------------------*/

#define  Fill_Zero 	 0		//���0
#define  Fill_Space 	 1		//���ո�

#define	Mode_H		 0		//LCDˮƽ��ʾ
#define	Mode_V		 1		//LCD������ʾ

#define 	FSMC_REG     0x60000000		// FSMC д�Ĵ�����ַ
#define 	FSMC_DATA    0x60020000		// FSMC д���ݵ�ַ

/*------------------------------------- LCD���ú� -------------------------------------*/

#define LCD_CS_PORT          GPIOD
#define LCD_CS_PIN           GPIO_Pin_7
#define LCD_CS_PINS          GPIO_PinSource7
#define LCD_CS_CLK           RCC_AHB1Periph_GPIOD

#define LCD_RS_PORT          GPIOD
#define LCD_RS_PIN           GPIO_Pin_11
#define LCD_RS_PINS          GPIO_PinSource11
#define LCD_RS_CLK           RCC_AHB1Periph_GPIOD

#define LCD_WR_PORT          GPIOD
#define LCD_WR_PIN           GPIO_Pin_5
#define LCD_WR_PINS          GPIO_PinSource5
#define LCD_WR_CLK           RCC_AHB1Periph_GPIOD

#define LCD_RD_PORT          GPIOD
#define LCD_RD_PIN           GPIO_Pin_4
#define LCD_RD_PINS          GPIO_PinSource4
#define LCD_RD_CLK           RCC_AHB1Periph_GPIOD

#define LCD_BL_PORT          GPIOD
#define LCD_BL_PIN           GPIO_Pin_12
#define LCD_BL_CLK           RCC_AHB1Periph_GPIOD

#define LCD_RST_PORT         GPIOC
#define LCD_RST_PIN          GPIO_Pin_2
#define LCD_RST_CLK          RCC_AHB1Periph_GPIOC

#define LCD_D0_PORT          GPIOD
#define LCD_D0_PIN           GPIO_Pin_14
#define LCD_D0_PINS          GPIO_PinSource14
#define LCD_D0_CLK           RCC_AHB1Periph_GPIOD

#define LCD_D1_PORT          GPIOD
#define LCD_D1_PIN           GPIO_Pin_15
#define LCD_D1_PINS          GPIO_PinSource15
#define LCD_D1_CLK           RCC_AHB1Periph_GPIOD

#define LCD_D2_PORT          GPIOD
#define LCD_D2_PIN           GPIO_Pin_0
#define LCD_D2_PINS          GPIO_PinSource0
#define LCD_D2_CLK           RCC_AHB1Periph_GPIOD

#define LCD_D3_PORT          GPIOD
#define LCD_D3_PIN           GPIO_Pin_1
#define LCD_D3_PINS          GPIO_PinSource1
#define LCD_D3_CLK           RCC_AHB1Periph_GPIOD

#define LCD_D4_PORT          GPIOE
#define LCD_D4_PIN           GPIO_Pin_7
#define LCD_D4_PINS          GPIO_PinSource7
#define LCD_D4_CLK           RCC_AHB1Periph_GPIOE

#define LCD_D5_PORT          GPIOE
#define LCD_D5_PIN           GPIO_Pin_8
#define LCD_D5_PINS          GPIO_PinSource8
#define LCD_D5_CLK           RCC_AHB1Periph_GPIOE

#define LCD_D6_PORT          GPIOE
#define LCD_D6_PIN           GPIO_Pin_9
#define LCD_D6_PINS          GPIO_PinSource9
#define LCD_D6_CLK           RCC_AHB1Periph_GPIOE

#define LCD_D7_PORT          GPIOE
#define LCD_D7_PIN           GPIO_Pin_10
#define LCD_D7_PINS          GPIO_PinSource10
#define LCD_D7_CLK           RCC_AHB1Periph_GPIOE

#define LCD_D8_PORT          GPIOE
#define LCD_D8_PIN           GPIO_Pin_11
#define LCD_D8_PINS          GPIO_PinSource11
#define LCD_D8_CLK           RCC_AHB1Periph_GPIOE

#define LCD_D9_PORT          GPIOE
#define LCD_D9_PIN           GPIO_Pin_12
#define LCD_D9_PINS          GPIO_PinSource12
#define LCD_D9_CLK           RCC_AHB1Periph_GPIOE

#define LCD_D10_PORT         GPIOE
#define LCD_D10_PIN          GPIO_Pin_13
#define LCD_D10_PINS         GPIO_PinSource13
#define LCD_D10_CLK          RCC_AHB1Periph_GPIOE

#define LCD_D11_PORT         GPIOE
#define LCD_D11_PIN          GPIO_Pin_14
#define LCD_D11_PINS         GPIO_PinSource14
#define LCD_D11_CLK          RCC_AHB1Periph_GPIOE

#define LCD_D12_PORT         GPIOE
#define LCD_D12_PIN          GPIO_Pin_15
#define LCD_D12_PINS         GPIO_PinSource15
#define LCD_D12_CLK          RCC_AHB1Periph_GPIOE

#define LCD_D13_PORT         GPIOD
#define LCD_D13_PIN          GPIO_Pin_8
#define LCD_D13_PINS         GPIO_PinSource8
#define LCD_D13_CLK          RCC_AHB1Periph_GPIOD

#define LCD_D14_PORT         GPIOD
#define LCD_D14_PIN          GPIO_Pin_9
#define LCD_D14_PINS         GPIO_PinSource9
#define LCD_D14_CLK          RCC_AHB1Periph_GPIOD

#define LCD_D15_PORT         GPIOD
#define LCD_D15_PIN          GPIO_Pin_10
#define LCD_D15_PINS         GPIO_PinSource10
#define LCD_D15_CLK          RCC_AHB1Periph_GPIOD

#define LCD_CLK              LCD_CS_CLK|LCD_RS_CLK|LCD_WR_CLK|LCD_RD_CLK|LCD_BL_CLK|LCD_RST_CLK|\
                             LCD_D0_CLK|LCD_D1_CLK|LCD_D2_CLK|LCD_D3_CLK|LCD_D4_CLK|LCD_D5_CLK|\
									  LCD_D6_CLK|LCD_D7_CLK|LCD_D8_CLK|LCD_D9_CLK|LCD_D10_CLK|LCD_D11_CLK|\
									  LCD_D12_CLK|LCD_D13_CLK|LCD_D14_CLK|LCD_D15_CLK

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  /*__LCD_H*/
	 
	 
