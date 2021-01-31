/*
 * uart.c
 *
 *  Created on: Jan 15, 2021
 *      Author: dukak
 */



#include "FreeRTOS.h"
#include "task.h"
#include "uart.h"
#include "queue.h"
#include "usart.h"

extern QueueHandle_t transmitQueueHandle;
extern QueueHandle_t receiveQueueHandle;
TaskHandle_t transmitHandle;
TaskHandle_t receiveHandle;


static void UART_Transmit(void* par){

	uint8_t buffer;
	while(1){

		xQueueReceive(transmitQueueHandle,&buffer,portMAX_DELAY);
		HAL_UART_Transmit_IT(&huart1, &buffer, sizeof(uint8_t));
		ulTaskNotifyTake(pdTRUE,portMAX_DELAY);

	}

}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance==huart1.Instance){

		BaseType_t woken=pdFALSE;
		vTaskNotifyGiveFromISR(transmitHandle,&woken);
		portYIELD_FROM_ISR(woken);


	}


}



static void UART_Receive(void* par){

	uint8_t buffer;
	while(1){


		HAL_UART_Receive_IT(&huart1, &buffer, sizeof(uint8_t));//iniciraj terminal da hoces da primas char
		ulTaskNotifyTake(pdTRUE,portMAX_DELAY);//cekaj dok ti terminal ne kaze da je poslao char
		xQueueSendToBack(receiveQueueHandle,&buffer,portMAX_DELAY);



	}

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance==huart1.Instance){

		BaseType_t woken=pdFALSE;
		vTaskNotifyGiveFromISR(receiveHandle,&woken);//javi task-u da si poslao char
		portYIELD_FROM_ISR(woken);


	}


}





void UART_Init(){


	xTaskCreate(UART_Transmit,"uart_task1",128, NULL,5,&transmitHandle);
	xTaskCreate(UART_Receive,"uart_task2",128, NULL,10,&receiveHandle);


}



