/*
 * uart.h
 *
 *  Created on: Jan 20, 2021
 *      Author: dukak
 */

#ifndef CORE_INC_UART_H_
#define CORE_INC_UART_H_

void UART_Init();
void transmitChar(char);
char receiveChar();
#endif /* CORE_INC_UART_H_ */
