/*
 * uart_driver.c
 *
 *  Created on: Jan 25, 2021
 *      Author: dukak
 */


#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "uart_driver.h"

#include "usart.h"
#include "string.h"

static UART_HandleTypeDef *phuart[2] =
{ &huart1, &huart2 };


//TRANSMIT

static TaskHandle_t UART_TxTaskHandle[2];
static QueueHandle_t UART_TxQueueHandle[2];
static SemaphoreHandle_t UART_TxMutexHandle[2];


static void UART_TxTask(void* par)
{

UART_Target target=(UART_Target) par;



uint8_t buffer;

while(1){

xQueueReceive(UART_TxQueueHandle[target],&buffer,portMAX_DELAY);
HAL_UART_Transmit_IT(phuart[target], &buffer, sizeof(uint8_t));

ulTaskNotifyTake(pdTRUE,portMAX_DELAY);//cekaj dok nije primio

}

}


void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){

	if(huart->Instance==huart1.Instance){

		BaseType_t woken=pdFALSE;
		vTaskNotifyGiveFromISR(UART_TxTaskHandle[VT],&woken);
		portYIELD_FROM_ISR( woken );

	}else if(huart->Instance==phuart[MCU]->Instance)
	{

		BaseType_t woken=pdFALSE;
			vTaskNotifyGiveFromISR(UART_TxTaskHandle[MCU],&woken);
			portYIELD_FROM_ISR( woken );



	}




}




//RECEIVE

static TaskHandle_t UART_RxTaskHandle[2];
static QueueHandle_t UART_RxQueueHandle[2];
static SemaphoreHandle_t UART_RxMutexHandle[2];


static void UART_RxTask(void* par)
{

	UART_Target target=(UART_Target) par;

	uint8_t buffer;

while(1){

	HAL_UART_Receive_IT(phuart[target], &buffer, sizeof(uint8_t));
	ulTaskNotifyTake(pdTRUE,portMAX_DELAY);//cekaj dok ne posalje
	xQueueSendToBack(UART_RxQueueHandle[target],&buffer,portMAX_DELAY);


}

}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){


	if(huart->Instance==huart1.Instance){

		BaseType_t woken=pdFALSE;
		vTaskNotifyGiveFromISR(UART_RxTaskHandle[VT],&woken);
		portYIELD_FROM_ISR( woken );

	}else if(huart->Instance==huart2.Instance)
	{

		BaseType_t woken=pdFALSE;
			vTaskNotifyGiveFromISR(UART_RxTaskHandle[MCU],&woken);
			portYIELD_FROM_ISR( woken );



	}


}



void UART_Init(){

	xTaskCreate(UART_TxTask,"task1",64,(void*) VT,4,&UART_TxTaskHandle[VT]);
	xTaskCreate(UART_RxTask,"task2",64,(void*) VT,20,&UART_RxTaskHandle[VT]);
	xTaskCreate(UART_TxTask,"task3",64,(void*) MCU,4,&UART_TxTaskHandle[MCU]);
	xTaskCreate(UART_RxTask,"task4",64,(void*) MCU,20,&UART_RxTaskHandle[MCU]);
UART_TxQueueHandle[VT]=xQueueCreate(64,sizeof(uint8_t));
UART_RxQueueHandle[VT]=xQueueCreate(64,sizeof(uint8_t));
UART_RxMutexHandle[VT]=xSemaphoreCreateMutex();
UART_TxMutexHandle[VT]=xSemaphoreCreateMutex();
UART_TxMutexHandle[MCU]=xSemaphoreCreateMutex();
UART_TxQueueHandle[MCU]=xQueueCreate(64,sizeof(uint8_t));

}



char* UART_BlockRxString(UART_Target target){


	xSemaphoreTake(UART_RxMutexHandle[target], portMAX_DELAY);

char* string=pvPortMalloc(64);


if(string!=NULL){
char c='\0';
uint32_t i=0;


	while(c!='\r' && i<64){
		xQueueReceive(UART_RxQueueHandle[target],&c,portMAX_DELAY);
string[i++]=c;

	}

	string[--i]=c;
}
xSemaphoreGive(UART_RxMutexHandle[target]);
return string;

}


void UART_BlockTxString(UART_Target target,char const* string){

	if(string!=NULL){
	xSemaphoreTake(UART_TxMutexHandle[target], portMAX_DELAY);
uint32_t i=0;

while(i<strlen(string) ){

	xQueueSendToBack(UART_TxQueueHandle[target],string+i,portMAX_DELAY);
i++;
}
xSemaphoreGive(UART_TxMutexHandle[target]);
	}


}

void UART_MotorCommandTx(UART_Target target,MotorCommand motorCommand){

xSemaphoreTake(UART_TxMutexHandle[target],portMAX_DELAY);
xQueueSendToBack(UART_TxQueueHandle[target],&motorCommand.motor,portMAX_DELAY);
xQueueSendToBack(UART_TxQueueHandle[target],&motorCommand.velocity,portMAX_DELAY);

xSemaphoreGive(UART_TxMutexHandle[target]);


}





//UART TRANSMIT
/* MCU1 salje podatak.. TX_TASK pokupi iz TX_REDA sta je MCU poslao
 * i posalje ga drugom uredjaju preko uart-a.. Ceka da UART kaze primio sam..
 * Ovde imamo slanja dva moguca uredjaja.. VT i MCU2..
 * Zato kada kreiramo TX_TASK kojim MCU salje podatke kao par prosledimo
 * i kome saljemo tj imamao 2 taska jedan za slanje VT drugi za slanje MCU2..
 * Imamo i dva reda za slanje TX_RED u zavisnosti kome saljemo..
 *
 */
//UART RECIVE
/*MCU1 prima podatke od VT ili MCU2..
*Imamo dva RX_Task koji primaju podatke i dve RX_REDA u koji cuvamo prijemni podatak
*u zav od toga ko je posla
 * nas uredja kupi podatak iz tog reda
 *
 *
 *
 */

/*

 *
 *
 */





