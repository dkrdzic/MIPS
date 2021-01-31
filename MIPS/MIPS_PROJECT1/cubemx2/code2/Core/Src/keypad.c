/*
 * keypad.c
 *
 *  Created on: Jan 29, 2021
 *      Author: dukak
 */


#include "FreeRTOS.h"
#include "task.h"
#include "gpio.h"
#include "lcd.h"
#include "timers.h"

static uint8_t keyReleased=1;
static uint8_t KEY_MAP[4][3]={

		{'1','2','3'},
		{'4','5','6'},
		{'7','8','9'},
		{'*','0','#'}
};

static TimerHandle_t timerHandle;
static TaskHandle_t taskHandle;
static void KEYPAD_Task(void* par){



	while(1){

		ulTaskNotifyTake(pdTRUE,portMAX_DELAY);

		if(keyReleased){

			for(uint32_t row=0;row<4;row++){


				GPIOB->ODR=0x01<<row;

				uint32_t activeColumn=(GPIOB->IDR>>4)&0x07;

				for(uint32_t column=0;column<3;column++){

					if(activeColumn&(0x01<<column)){
						send(Instruction,0x80);
						send(Data,KEY_MAP[row][column]);
						keyReleased=0;
						xTimerStart(timerHandle,portMAX_DELAY);

					}

				}



			}




		}

GPIOB->ODR=0x0F;

	}


}

void timerCallback( TimerHandle_t xTimer ){




		if(keyReleased==0){


			if(((GPIOB->IDR>>4)&0x07)==0){
				keyReleased=1;


			}else xTimerStart(timerHandle,portMAX_DELAY);

		}






}




void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){



	if(GPIO_Pin==GPIO_PIN_7){
		BaseType_t woken=pdFALSE;
		vTaskNotifyGiveFromISR(taskHandle,&woken);
		 portYIELD_FROM_ISR( woken );

	}


}



void KEYPAD_Init(){
	GPIOB->ODR=0x0F;
	xTaskCreate(KEYPAD_Task,"keyPad",64,NULL,50,&taskHandle);
	timerHandle=xTimerCreate("Timer",50,pdFALSE,NULL,timerCallback);



}
