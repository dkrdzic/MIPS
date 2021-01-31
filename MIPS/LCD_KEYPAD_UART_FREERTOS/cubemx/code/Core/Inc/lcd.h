/*
 * lcd.h
 *
 *  Created on: Jan 17, 2021
 *      Author: dukak
 */

#ifndef CORE_INC_LCD_H_
#define CORE_INC_LCD_H_


typedef enum{

	Instruction=0,Data=1

}RS_DataType;

typedef struct{
	RS_DataType RS;
	uint8_t DB;

}Item;

void LCD_Init();
void send(RS_DataType,uint8_t);

#endif /* CORE_INC_LCD_H_ */
