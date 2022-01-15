#ifndef __TEST_H
#define __TEST_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

#include "sys.h"
#include "lcd_3.5tft.h"
#include "delay.h"

void LCD_ClearTest(void);			// ��������
void LCD_TextTest(void);			// �ı���ʾ����
void LCD_FillTest(void);			// ����������
void LCD_ColorTest(void);			// ��ɫ����
void LCD_GrahicTest(void);			// ��ͼ����
void LCD_HorizontalText(void);	// ��������

#ifdef __cplusplus
}
#endif /* __cplusplus */
	 
#endif
