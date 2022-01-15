#ifndef __KEY_H
#define __KEY_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

#include "sys.h"
#include "delay.h"

#define	KEY_ON	 1		//��������
#define	KEY_OFF	 0		//�����ſ�

/*---------------------- �������ú� ------------------------*/

#define KEY_PIN           GPIO_Pin_15        		 // KEY ����      
#define KEY_PORT          GPIOA                     // KEY GPIO�˿�     
#define KEY_CLK           RCC_AHB1Periph_GPIOA	    // KEY GPIO�˿�ʱ��

/*---------------------- �������� ----------------------------*/

void 	KEY_Init(void);	//����IO�ڳ�ʼ������
u8		KEY_Scan(void);   //����ɨ��

#ifdef __cplusplus
}
#endif /* __cplusplus */
	 
#endif //__KEY_H


