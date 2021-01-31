/*
 * uart_driver.h
 *
 *  Created on: Jan 28, 2021
 *      Author: dukak
 */

#ifndef CORE_INC_UART_DRIVER_H_
#define CORE_INC_UART_DRIVER_H_

#include "work.h"

typedef enum{

	VT=0,MCU
}Target;


void UART_Init();


void transmitString(Target target,const char* string);

char* receiveString(Target target);
void transmitMotorCommand(Target target, MotorCommand mc);

#endif /* CORE_INC_UART_DRIVER_H_ */
