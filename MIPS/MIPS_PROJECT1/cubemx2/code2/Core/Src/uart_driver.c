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




TaskHandle_t UART_RxTaskHandle;

QueueHandle_t UART_RxQueueHandle;

SemaphoreHandle_t UART_RxMutexHandle;









//RECEIVE


static void UART_ReceiveTask(void* par){

	uint8_t buffer;

	while(1){
		HAL_UART_Receive_IT(&huart1, &buffer, sizeof(uint8_t));
		ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
		xQueueSendToBack(UART_RxQueueHandle,&buffer,portMAX_DELAY);



	}



}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){

	BaseType_t woken=pdFALSE;


	if(huart->Instance==huart1.Instance){

		vTaskNotifyGiveFromISR(UART_RxTaskHandle,&woken);


	}


	portYIELD_FROM_ISR(woken );

}



void UART_Init()
{



	xTaskCreate(UART_ReceiveTask,"task3",128,NULL,20,&UART_RxTaskHandle);




	UART_RxQueueHandle=xQueueCreate(64,sizeof(uint8_t));




	UART_RxMutexHandle=xSemaphoreCreateMutex();
}








MotorCommand receiveMotorCommand(){

MotorCommand mc;

		xSemaphoreTake(UART_RxMutexHandle,portMAX_DELAY);

		xQueueReceive(UART_RxQueueHandle,&mc.motor,portMAX_DELAY);
		xQueueReceive(UART_RxQueueHandle,&mc.velocity,portMAX_DELAY);


		xSemaphoreGive(UART_RxMutexHandle);

return mc;


}



