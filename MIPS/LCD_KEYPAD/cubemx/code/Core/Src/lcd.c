/*
 * lcd.c
 *
 *  Created on: Jan 10, 2021
 *      Author: dukak
 */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "lcd.h"
#include "gpio.h"


QueueHandle_t queueHandle;

static void LCD_Write(RS_DataType rs,uint8_t val)
{

	GPIOC->ODR=((rs & 0x01)<<5) | (val & 0x0F);
	GPIOC->ODR|=0x40;
	GPIOC->ODR&=~(0x40);

}


static void LCD_CommandInitiate(RS_DataType rs,uint8_t val)
{

	LCD_Write(rs,val>>4);
	LCD_Write(rs,val);
	vTaskDelay(2); //cekaj izmedju svake komande

}



static void LCD_Task(void* par){


	vTaskDelay(20);//moramo cekati 20 tickova (20ms) zbog reseta

	LCD_Write(Instruction,0x02); //da kazemo da hocemo 4b interface
	vTaskDelay(2);

	LCD_CommandInitiate(Instruction,0x28); //function set
	LCD_CommandInitiate(Instruction,0x0C);//Display on/of control inst
	LCD_CommandInitiate(Instruction,0x06);// entry mode

	LCD_CommandInitiate(Instruction, 0x02);

Item item;

	while(1){


		xQueueReceive(queueHandle,&item,portMAX_DELAY);
		LCD_CommandInitiate(item.rs, item.val);

	}
}


	void LCD_Init(){

		queueHandle=xQueueCreate(64,sizeof(Item));
		xTaskCreate(LCD_Task,"LCD_Task",128,NULL,2,NULL);


	}


void send(RS_DataType rs,uint8_t val)
{
	Item item={rs,val};

	xQueueSend(queueHandle,&item,portMAX_DELAY);



}




