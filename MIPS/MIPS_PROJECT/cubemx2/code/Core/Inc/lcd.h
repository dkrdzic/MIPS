/*
 * lcd.h
 *
 *  Created on: Jan 26, 2021
 *      Author: dukak
 */

#ifndef CORE_INC_LCD_H_
#define CORE_INC_LCD_H_


typedef enum{

	Instruction=0,Data

}RS_DataType;

typedef struct{

	RS_DataType rs;
	uint8_t data;

}LCD_Type;

void LCD_Init();
void send(RS_DataType,uint8_t);


#endif /* CORE_INC_LCD_H_ */
