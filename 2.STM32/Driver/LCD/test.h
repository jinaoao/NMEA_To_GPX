#ifndef __TEST_H
#define __TEST_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

#include "sys.h"
#include "lcd_3.5tft.h"
#include "delay.h"

void LCD_ClearTest(void);			// ÇåÆÁ²âÊÔ
void LCD_TextTest(void);			// ÎÄ±¾ÏÔÊ¾²âÊÔ
void LCD_FillTest(void);			// ¾ØĞÎÌî³ä²âÊÔ
void LCD_ColorTest(void);			// ÑÕÉ«²âÊÔ
void LCD_GrahicTest(void);			// »æÍ¼²âÊÔ
void LCD_HorizontalText(void);	// ºáÆÁ²âÊÔ

#ifdef __cplusplus
}
#endif /* __cplusplus */
	 
#endif
