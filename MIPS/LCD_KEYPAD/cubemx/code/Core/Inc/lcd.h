/*
 * lcd.h
 *
 *  Created on: Jan 10, 2021
 *      Author: dukak
 */

#ifndef CORE_INC_LCD_H_
#define CORE_INC_LCD_H_


#include "stdint.h"

typedef enum{

	Instruction=0, Data

}RS_DataType;


typedef struct{
	RS_DataType rs;
	uint8_t val;
}Item;

void LCD_Init();
void send(RS_DataType,uint8_t);



#endif /* CORE_INC_LCD_H_ */
