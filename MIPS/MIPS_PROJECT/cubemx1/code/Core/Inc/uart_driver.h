/*
 * uart_driver.h
 *
 *  Created on: Jan 25, 2021
 *      Author: dukak
 */

#ifndef CORE_INC_UART_DRIVER_H_
#define CORE_INC_UART_DRIVER_H_
#include "work.h"



typedef enum
{
	VT=0,MCU
	}UART_Target;

void UART_Init();

void UART_BlockTxString(UART_Target target,char const* string);
char* UART_BlockRxString(UART_Target target);
void UART_MotorCommandTx(UART_Target target,MotorCommand motorCommand);

#endif /* CORE_INC_UART_DRIVER_H_ */
