/*
 * key.c
 *
 *  Created on: Jan 18, 2021
 *      Author: dukak
 */


#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "lcd.h"
#include "gpio.h"
#include "timers.h"

TaskHandle_t KEY_taskHandle;
TimerHandle_t timerHandle;

static uint8_t KEY_released=1;

static char KEY_MAP[4][3]={
		{'1','2','3'},
		{'4','5','6'},
		{'7','8','9'},
		{'*','0','#'}
		};

static void KEY_Task(void* par){


	while(1){

		ulTaskNotifyTake(pdTRUE,portMAX_DELAY);

		if(KEY_released){


			for(uint8_t row=0;row<4;row++){

				GPIOB->ODR=0x01<<row;

				uint32_t selectedColumn=(GPIOB->IDR>>4)&0x07;

				for(uint8_t column=0;column<3;column++){

					if(selectedColumn & (0x01<<column)){

						send(Instruction,0xC8);
						send(Data,KEY_MAP[row][column]);
						KEY_released=0;
						xTimerStart(timerHandle,portMAX_DELAY);
					}


				}

			}




		}

		GPIOB->ODR=0x0F;

	}

}



void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){

if(GPIO_Pin==GPIO_PIN_7){


	BaseType_t woken=pdFALSE;
	vTaskNotifyGiveFromISR(KEY_taskHandle,&woken);
	 portYIELD_FROM_ISR( woken );


}

}

static void timerCallback(TimerHandle_t timer){

	if(KEY_released==0){

		if(((GPIOB->IDR>>4)&0x07)==0){

			KEY_released=1;

		}else{

			xTimerStart(timerHandle,portMAX_DELAY);
		}

	}


}


void KEY_Init(){

	GPIOB->ODR=0x0F;
	xTaskCreate(KEY_Task,"key_task",128,NULL,10,&KEY_taskHandle);
	timerHandle=xTimerCreate("timer",50,pdFALSE,NULL,timerCallback);

}








