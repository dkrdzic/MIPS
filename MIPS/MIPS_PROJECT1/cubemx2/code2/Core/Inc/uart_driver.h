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
MotorCommand receiveMotorCommand();

#endif /* CORE_INC_UART_DRIVER_H_ */
