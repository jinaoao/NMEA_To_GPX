#ifndef __LCD_H
#define __LCD_H		

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

#include "sys.h"
#include "lcd_fonts.h"
#include "stdint.h"
#include "stdio.h"

/*--------------------------------------- 常用颜色 ----------------------------------*/
//	 虽然反客3.5寸的屏幕使用的颜色格式是16位的RGB565，但是这里为了方便用户使用，
//	 入口参数使用的是24位的RGB888颜色，然后再通过代码自动转换成16位色。用户可以很方便
//	 的在电脑用取色器获取24位的颜色，再将此24位颜色输入LCD_SetColor()或LCD_SetBackColor()
//  就可以要显示出相应的颜色。

#define 	LCD_WHITE       0xFFFFFF	// 白色
#define 	LCD_BLACK       0x000000	// 黑色
                           
#define 	LCD_BLUE        0x0000FF	// 蓝色
#define 	LCD_GREEN       0x00FF00   // 绿色
#define 	LCD_RED         0xFF0000   // 红色
#define 	LCD_CYAN        0x00FFFF   // 蓝绿色
#define 	LCD_MAGENTA     0xFF00FF   // 紫色
#define 	LCD_YELLOW      0xFFFF00   // 黄色
#define 	LCD_GREY        0x2C2C2C   // 灰色
                                    
#define 	LIGHT_BLUE      0x8080FF   // 亮蓝色
#define 	LIGHT_GREEN     0x80FF80   // 亮绿色
#define 	LIGHT_RED       0xFF8080   // 亮红色
#define 	LIGHT_CYAN      0x80FFFF   // 亮蓝绿色
#define 	LIGHT_MAGENTA   0xFF80FF   // 亮紫色
#define 	LIGHT_YELLOW    0xFFFF80   // 亮黄色
#define 	LIGHT_GREY      0xA3A3A3   // 亮灰色
                                     
#define 	DARK_BLUE       0x000080   // 暗蓝色
#define 	DARK_GREEN      0x008000   // 暗绿色
#define 	DARK_RED        0x800000   // 暗红色
#define 	DARK_CYAN       0x008080   // 暗蓝绿色
#define 	DARK_MAGENTA    0x800080   // 暗紫色
#define 	DARK_YELLOW     0x808000   // 暗黄色
#define 	DARK_GREY       0x404040   // 暗灰色

/*------------------------------------- 函数声明 -------------------------------------*/

void 	LCD_Init(void);	// 初始化LCD
void 	LCD_Clear(void);	// 清屏

void 	LCD_SetColor(u32 Color);			// 设置画笔颜色
void 	LCD_SetBackColor(u32 Color);		// 设置背景色
void 	LCD_SetFont(pFONT *fonts);			// 设置字体
void 	LCD_SetCursor(u16 x, u16 y);		// 设置坐标
void 	LCD_DisplayMode(u8 direction);   // 设置显示方向

void 	LCD_DisplayChar(u16 x, u16 y,u8 add);							// 在指定坐标处显示单个ASCII字符
void 	LCD_DisplayString( u16 x, u16 y, u8 *p);						// 在指定坐标处显示字符串
void 	LCD_ShowNumMode(u8 mode);											// 设置数字显示的填充模式
void 	LCD_DisplayNumber( u16 x, u16 y, u32 number, u8 len) ;   // 显示十进制数

void	LCD_DrawPoint(u16 x,u16 y);					// 画点
void  LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);		// 画线
void  LCD_DrawRect(u16 x, u16 y, u16 width, u16 height);	// 画矩形
void  LCD_DrawCircle(u16 x, u16 y, u16 r);					// 画圆
void  LCD_DrawEllipse(int x, int y, int r1, int r2);		// 画椭圆

void  LCD_FillRect(u16 x, u16 y, u16 width, u16 height);		// 填充矩形
void  LCD_FillCircle(u16 x, u16 y, u16 r);						// 填充圆
void LCD_Color_Fill(u16 x1, u16 y1, u16 x2, u16 y2, u16 *color); //在指定区域内填充指定颜色块	

/*-------------------------------LCD相关参数宏定义-------------------------------------*/

#define  Fill_Zero 	 0		//填充0
#define  Fill_Space 	 1		//填充空格

#define	Mode_H		 0		//LCD水平显示
#define	Mode_V		 1		//LCD竖屏显示

#define 	FSMC_REG     0x60000000		// FSMC 写寄存器地址
#define 	FSMC_DATA    0x60020000		// FSMC 写数据地址

/*------------------------------------- LCD配置宏 -------------------------------------*/

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
	 
	 
