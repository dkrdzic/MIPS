/*
 * uart.c
 *
 *  Created on: Jan 20, 2021
 *      Author: dukak
 */

#include "usart.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "uart.h"
#include "gpio.h"

TaskHandle_t taskTransmitHandle;
QueueHandle_t queueTransmitHandle;

TaskHandle_t taskReceiveHandle;
QueueHandle_t queueReceiveHandle;


static void UART_Transmit(void* param){

uint8_t buffer;
	while(1){

		xQueueReceive(queueTransmitHandle,&buffer,portMAX_DELAY);
		  HAL_UART_Transmit_IT(&huart1,&buffer , sizeof(uint8_t));
		  ulTaskNotifyTake(pdTRUE,portMAX_DELAY);



	}

}



void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){

	if(huart->Instance==huart1.Instance){

		BaseType_t woken=pdFALSE;
		vTaskNotifyGiveFromISR( taskTransmitHandle,&woken );

		portYIELD_FROM_ISR( woken );
	}



}

static void UART_Receive(void* param){

uint8_t buffer;
	while(1){

		HAL_UART_Receive_IT(&huart1, &buffer, sizeof(uint8_t));
		 ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
		xQueueSendToBack(queueReceiveHandle,&buffer,portMAX_DELAY);





	}

}




void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){

	if(huart->Instance==huart1.Instance){

		BaseType_t woken=pdFALSE;
		vTaskNotifyGiveFromISR( taskReceiveHandle,&woken );

		portYIELD_FROM_ISR( woken );
	}

}




void UART_Init(){


	xTaskCreate(UART_Transmit,"uart_task",128,NULL,9,&taskTransmitHandle);
queueTransmitHandle=xQueueCreate(64,sizeof(uint8_t));

xTaskCreate(UART_Receive,"uart_task_receive",128,NULL,9,&taskReceiveHandle);
queueReceiveHandle=xQueueCreate(64,sizeof(uint8_t));
}

void transmitChar(char a){

	xQueueSendToBack(queueTransmitHandle,&a,portMAX_DELAY);



}

char receiveChar(){

	char a;
	xQueueReceive(queueReceiveHandle,&a,portMAX_DELAY);
return a;


}





