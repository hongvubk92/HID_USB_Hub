/*
 * HC05_HID.h
 *
 *  Created on: Mar 3, 2018
 *      Author: Administrator
 */

#ifndef HC05_HID_HC05_HID_H_
#define HC05_HID_HC05_HID_H_
/* Include core modules */
#include "stm32f4xx.h"
#include "tm_stm32f4_usart.h"

#define HC05_HID_WRITE(c)		TM_USART_Putc(USART1, c);
void HC05_HID_COM_Init(void);

#endif /* HC05_HID_HC05_HID_H_ */
