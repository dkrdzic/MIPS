/*
 * lcd.c
 *
 *  Created on: Jan 26, 2021
 *      Author: dukak
 */



#include "FreeRTOS.h"
#include "lcd.h"
#include "gpio.h"
#include "task.h"
#include "queue.h"

static QueueHandle_t LCD_QueueHandle;


static void LCD_Write(RS_DataType rs,uint8_t data )
{
	GPIOC->ODR=(((rs&0x01)<<5)|(data&0x0F));

	GPIOC->ODR|=0x40;
	GPIOC->ODR&=~0x40;

}



static void Send4Bit(RS_DataType rs,uint8_t data){

	LCD_Write(rs,data>>4);
	LCD_Write(rs,data);
	vTaskDelay(2);




}




static void LCD_Task(void* par){


	vTaskDelay(20);

	LCD_Write(Instruction,0x02);
	vTaskDelay(2);

	Send4Bit(Instruction,0x28);
	Send4Bit(Instruction,0x0C);
	Send4Bit(Instruction,0x06);

	Send4Bit(Instruction,0x02);



LCD_Type buffer;
	while(1){

		xQueueReceive(LCD_QueueHandle,&buffer,portMAX_DELAY);
Send4Bit(buffer.rs,buffer.data);

	}

}



void LCD_Init(){


	xTaskCreate(LCD_Task,"task",128,NULL,2,NULL);

	LCD_QueueHandle=xQueueCreate(64,sizeof(LCD_Type));
}

void send(RS_DataType rs,uint8_t data){

	LCD_Type buffer={rs,data};
	xQueueSend(LCD_QueueHandle,&buffer,portMAX_DELAY);


}





