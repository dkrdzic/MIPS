/*
 * uart_driver.c
 *
 *  Created on: Jan 26, 2021
 *      Author: dukak
 */


#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "usart.h"
#include "work.h"

TaskHandle_t UART_RxTaskHandle;
QueueHandle_t UART_RxQueueHandle;
SemaphoreHandle_t UART_RxMutexHandle;

static void UART_RxTask(void* par){


	uint8_t buffer;
while(1){

	HAL_UART_Receive_IT(&huart1, &buffer, sizeof(uint8_t));
	ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
	xQueueSendToBack(UART_RxQueueHandle,&buffer,portMAX_DELAY);
}


}




void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){



		BaseType_t woken=pdFALSE;
		vTaskNotifyGiveFromISR(UART_RxTaskHandle,&woken);
		 portYIELD_FROM_ISR(woken);





}







void UART_Init(){

xTaskCreate(UART_RxTask,"rx_task",128,NULL,20,&UART_RxTaskHandle);
UART_RxQueueHandle=xQueueCreate(128,sizeof(uint8_t));
UART_RxMutexHandle=xSemaphoreCreateMutex();

}





MotorCommand RxMotorCommand(){

	xSemaphoreTake(UART_RxMutexHandle,portMAX_DELAY);

	MotorCommand motorCommand={0,0};

	xQueueReceive(UART_RxQueueHandle,&motorCommand.motor,portMAX_DELAY);
	xQueueReceive(UART_RxQueueHandle,&motorCommand.velocity,portMAX_DELAY);



	xSemaphoreGive(UART_RxMutexHandle);

	return motorCommand;




}

















