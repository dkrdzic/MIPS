/*
 * uart_driver.c
 *
 *  Created on: Jan 28, 2021
 *      Author: dukak
 */


#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "usart.h"
#include "uart_driver.h"
#include "string.h"
#include "work.h"

UART_HandleTypeDef* phuart[2]={&huart1,&huart2};

TaskHandle_t UART_TxTaskHandle[2];
TaskHandle_t UART_RxTaskHandle[2];
QueueHandle_t UART_TxQueueHandle[2];
QueueHandle_t UART_RxQueueHandle[2];
SemaphoreHandle_t UART_TxMutexHandle[2];
SemaphoreHandle_t UART_RxMutexHandle[2];



//TRANSMIT


static void UART_TransmitTask(void* par){

Target target = (Target)par;
uint8_t buffer;

while(1){

	xQueueReceive(UART_TxQueueHandle[target],&buffer,portMAX_DELAY);
	HAL_UART_Transmit_IT(phuart[target], &buffer, sizeof(uint8_t));
	ulTaskNotifyTake(pdTRUE,portMAX_DELAY);

}


}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
	BaseType_t woken=pdFALSE;


	if(huart->Instance==huart1.Instance){//VT

		vTaskNotifyGiveFromISR(UART_TxTaskHandle[VT],&woken);




	}else if(huart->Instance==huart2.Instance){//MCU
		vTaskNotifyGiveFromISR(UART_TxTaskHandle[MCU],&woken);

	}


	portYIELD_FROM_ISR(woken );

}





//RECEIVE


static void UART_ReceiveTask(void* par){

	Target target = (Target)par;
	uint8_t buffer;

	while(1){
		HAL_UART_Receive_IT(phuart[target], &buffer, sizeof(uint8_t));
		ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
		xQueueSendToBack(UART_RxQueueHandle[target],&buffer,portMAX_DELAY);



	}



}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){

	BaseType_t woken=pdFALSE;


	if(huart->Instance==huart1.Instance){//VT

		vTaskNotifyGiveFromISR(UART_RxTaskHandle[VT],&woken);




	}else if(huart->Instance==huart2.Instance){//MCU
		vTaskNotifyGiveFromISR(UART_RxTaskHandle[MCU],&woken);

	}


	portYIELD_FROM_ISR(woken );

}



void UART_Init()
{

	xTaskCreate(UART_TransmitTask,"task1",64,(void*) MCU,4,&UART_TxTaskHandle[MCU]);
	xTaskCreate(UART_TransmitTask,"task2",64,(void*) VT,4,&UART_TxTaskHandle[VT]);

	xTaskCreate(UART_ReceiveTask,"task3",64,(void*) MCU,20,&UART_RxTaskHandle[MCU]);
	xTaskCreate(UART_ReceiveTask,"task4",64,(void*)VT,20,&UART_RxTaskHandle[VT]);

	UART_TxQueueHandle[MCU]=xQueueCreate(64,sizeof(uint8_t));
	UART_TxQueueHandle[VT]=xQueueCreate(64,sizeof(uint8_t));

	UART_RxQueueHandle[MCU]=xQueueCreate(64,sizeof(uint8_t));
	UART_RxQueueHandle[VT]=xQueueCreate(64,sizeof(uint8_t));

	UART_TxMutexHandle[MCU]=xSemaphoreCreateMutex();
	UART_TxMutexHandle[VT]=xSemaphoreCreateMutex();

	UART_RxMutexHandle[MCU]=xSemaphoreCreateMutex();
	UART_RxMutexHandle[VT]=xSemaphoreCreateMutex();
}




void transmitString(Target target, char const* string){

	if(string!=NULL){

		xSemaphoreTake(UART_TxMutexHandle[target],portMAX_DELAY);


		for(uint32_t i=0;i<strlen(string);i++){
			xQueueSendToBack(UART_TxQueueHandle[target],string+i,portMAX_DELAY);

		}


		xSemaphoreGive(UART_TxMutexHandle[target]);
	}



}

char* receiveString(Target target){

	xSemaphoreTake(UART_RxMutexHandle[target],portMAX_DELAY);
	char* string=pvPortMalloc(64);

	if(string!=NULL){

		char c='\0';
		uint32_t i=0;

		while(c!='\r' && i<64){

			xQueueReceive(UART_RxQueueHandle[target],&c,portMAX_DELAY);
			string[i++]=c;


		}
		string[--i]='\0';


	}


		xSemaphoreGive(UART_RxMutexHandle[target]);
return string;
}


void transmitMotorCommand(Target target, MotorCommand mc){



		xSemaphoreTake(UART_TxMutexHandle[target],portMAX_DELAY);

		xQueueSendToBack(UART_TxQueueHandle[target],&mc.motor,portMAX_DELAY);
		xQueueSendToBack(UART_TxQueueHandle[target],&mc.velocity,portMAX_DELAY);


		xSemaphoreGive(UART_TxMutexHandle[target]);




}



