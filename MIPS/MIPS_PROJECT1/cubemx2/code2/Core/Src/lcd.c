/*
 * lcd.c
 *
 *  Created on: Jan 28, 2021
 *      Author: dukak
 */



#include "lcd.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "gpio.h"


QueueHandle_t queueHandle;


static void LCD_Write(RS rs,uint8_t data){


GPIOC->ODR=(((rs &0x01)<<5)|(data&0x0F));

GPIOC->ODR|=0x40;
GPIOC->ODR&=~0x40;

}


static void Send4Bit(RS rs, uint8_t data){

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

	Item item;
	while(1){


		xQueueReceive(queueHandle,&item,portMAX_DELAY);
		Send4Bit(item.rs,item.data);

	}

}


void LCD_Init(){

	xTaskCreate(LCD_Task,"task_lcd",128,NULL,2,NULL);

queueHandle=xQueueCreate(64,sizeof(Item));

}





void send(RS rs, uint8_t data){

	Item item={rs, data};

	xQueueSendToBack(queueHandle,&item,portMAX_DELAY);



}



