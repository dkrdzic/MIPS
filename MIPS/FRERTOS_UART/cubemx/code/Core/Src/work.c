/*
 * wok.c
 *
 *  Created on: Jan 15, 2021
 *      Author: dukak
 */

#include "FreeRTOS.h"
#include "task.h"
#include "uart.h"
#include "queue.h"
#include "usart.h"
#include "semphr.h"
#include "string.h"


QueueHandle_t transmitQueueHandle;
QueueHandle_t receiveQueueHandle;
TaskHandle_t workHandle;
SemaphoreHandle_t semHandle;


static void workTask(void* par){

	char item;
	char* string;
 uint32_t index;
	while(1){

	xQueueReceive(receiveQueueHandle,&item,portMAX_DELAY);
	string=pvPortMalloc(64);
	index=0;
	xSemaphoreTake(semHandle,portMAX_DELAY);
	if(string!=NULL){

		while(item!='\r' && index<64){
			xQueueReceive(receiveQueueHandle,&item,portMAX_DELAY);
			string[index++]=item;
		}

		string[--index]='\0';
	}
	xSemaphoreGive(semHandle);

	xSemaphoreTake(semHandle,portMAX_DELAY);
	for(uint32_t i=0;i<strlen(string);i++){
		xQueueSendToBack(transmitQueueHandle,string+i,portMAX_DELAY);
	}
	xSemaphoreGive(semHandle);


vPortFree(string);

/*
		item='a';
		xQueueSendToBack(transmitQueueHandle,&item,portMAX_DELAY);


		item='\r';
	xQueueSendToBack(transmitQueueHandle,&item,portMAX_DELAY);


string="Dule car!\r";
xSemaphoreTake(semHandle,portMAX_DELAY);
for(uint32_t i=0;i<strlen(string);i++){
	xQueueSendToBack(transmitQueueHandle,string+i,portMAX_DELAY);
}
xSemaphoreGive(semHandle);


uint32_t digit=123;
char digitString[32];
uint32_t index=32;
xSemaphoreTake(semHandle,portMAX_DELAY);
while(digit!=0 && index>0){
	digitString[--index]='0'+digit%10;
	digit=digit/10;

}
for(uint32_t i=index;i<32;i++){
	xQueueSendToBack(transmitQueueHandle,digitString+i,portMAX_DELAY);
}
xSemaphoreGive(semHandle);

item='\r';
xQueueSendToBack(transmitQueueHandle,&item,portMAX_DELAY);
*/
vTaskDelay(1000);


}

}


void workInit(){
	UART_Init();
	xTaskCreate(workTask,"work_task",128, NULL,5,&workHandle);
	transmitQueueHandle=xQueueCreate(64,sizeof(uint8_t));
	receiveQueueHandle=xQueueCreate(64,sizeof(uint8_t));
	semHandle=xSemaphoreCreateMutex();
}



