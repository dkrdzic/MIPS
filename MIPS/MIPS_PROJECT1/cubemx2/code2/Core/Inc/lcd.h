/*
 * lcd.h
 *
 *  Created on: Jan 28, 2021
 *      Author: dukak
 */

#ifndef CORE_INC_LCD_H_
#define CORE_INC_LCD_H_


#include <stdint.h>

typedef enum{

	Instruction=0, Data

}RS;



typedef struct{
	RS rs;
	uint8_t data;

}Item;



void LCD_Init();


void send(RS rs, uint8_t data);

#endif /* CORE_INC_LCD_H_ */
