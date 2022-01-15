#ifndef __LED_H
#define __LED_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

#include "sys.h"

/*---------------------- LED���ú� ------------------------*/

#define LED1_PIN             GPIO_Pin_0       		 // LED1 ����      
#define LED1_PORT            GPIOC                  // LED1 GPIO�˿�     
#define LED1_CLK             RCC_AHB1Periph_GPIOC	 // LED1 GPIO�˿�ʱ��

/*---------------------- LED���ƺ� ------------------------*/
					
#define LED1_ON 	  GPIO_ResetBits(LED1_PORT,LED1_PIN);	// ����͵�ƽ������LED1	
#define LED1_OFF 	  GPIO_SetBits(LED1_PORT,LED1_PIN);		// ����ߵ�ƽ���ر�LED1	

/*---------------------- �������� ----------------------------*/

void LED_Init(void);	//LED��ʼ������

	 
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //__LED_H

