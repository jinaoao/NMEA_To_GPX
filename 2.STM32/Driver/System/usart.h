#ifndef __USART_H
#define __USART_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 

void uart_init(u32 bound);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif


