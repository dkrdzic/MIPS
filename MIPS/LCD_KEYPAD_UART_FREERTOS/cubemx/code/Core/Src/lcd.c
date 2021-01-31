/*
 * lcd.c
 *
 *  Created on: Jan 17, 2021
 *      Author: dukak
 */

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "lcd.h"
#include "gpio.h"


QueueHandle_t LCD_QueueHandle;

static void LCD_Write(RS_DataType RS,uint8_t DB){


	GPIOC->ODR=((RS&0x01)<<5) |(DB & 0x0F);

	GPIOC->ODR|=0x40;
	GPIOC->ODR&=(~0x40);


}


static void LCD_4BitTransfer(RS_DataType RS,uint8_t DB){

	LCD_Write(RS,DB>>4);
	LCD_Write(RS,DB);
	vTaskDelay(2);

}




static void LCD_Task(void* param){

	vTaskDelay(20);

	LCD_Write(Instruction,0x02);
	vTaskDelay(2);

	LCD_4BitTransfer(Instruction,0x28);
	LCD_4BitTransfer(Instruction,0x0C);
	LCD_4BitTransfer(Instruction,0x06);

	LCD_4BitTransfer(Instruction,0x02);

	Item item;
	while(1){

		xQueueReceive(LCD_QueueHandle,&item,portMAX_DELAY);
		LCD_4BitTransfer(item.RS,item.DB);

	}

}



void LCD_Init(){

	LCD_QueueHandle=xQueueCreate(64,sizeof(Item));
	xTaskCreate(LCD_Task,"lcd_task",128,NULL,4,NULL);

}


void send(RS_DataType RS,uint8_t DB){

Item	item={RS,DB};
	xQueueSendToBack(LCD_QueueHandle,&item,portMAX_DELAY);


}


