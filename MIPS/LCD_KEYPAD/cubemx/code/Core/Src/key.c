/*
 * key.c
 *
 *  Created on: Jan 12, 2021
 *      Author: dukak
 */


#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "gpio.h"
#include "key.h"
#include "lcd.h"

static void KEY_Task(void*);
static void KEY_TimerCallback(TimerHandle_t);
static char KEY_Map[4][3] =
{
{ '1', '2', '3' },
{ '4', '5', '6' },
{ '7', '8', '9' },
{ '*', '0', '#' } };


static uint8_t KEY_PreviousReleased=1;

TaskHandle_t taskHandle;
TimerHandle_t timerHandle;

void KEY_Init(){
	GPIOB->ODR=0x0F;
	xTaskCreate(KEY_Task,"KEY_Task",128,NULL,10,&taskHandle);
	timerHandle=xTimerCreate("Timer",50,pdFALSE,NULL,KEY_TimerCallback);
}


static void KEY_Task(void* par){


	while(1){

		ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
if(KEY_PreviousReleased){
		for(uint8_t row=0;row<4;row++)
		{
			GPIOB->ODR=0x01<<row;
			uint32_t activeColumn=(GPIOB->IDR>>4)&0x07; //ovo ce biti aktivno ako je odg row (u kom je taster kliknut) 1
			for(uint8_t column=0;column<3;column++){

				if(activeColumn&(0x01<<column)){

					send(Data,KEY_Map[row][column]);
					KEY_PreviousReleased=0;
					xTimerStart(timerHandle,portMAX_DELAY);//startuj da proverava kada ce da se otpusti
				}

			}


		}
}
GPIOB->ODR=0x0F;

	}




}

static void KEY_TimerCallback(TimerHandle_t timer){

	if(!KEY_PreviousReleased){//ako je vec bilo kliknuto,tj drzi se taster

		if (((GPIOB->IDR >> 4) & 0x07) == 0)
				{
					KEY_PreviousReleased = 1;
				}//otpusteno mozes opet racunati kad se klikne
				else
				{
					xTimerStart(timerHandle, portMAX_DELAY);
				}//jos nije otpusteno, startuj opet proveru


	}


}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){

	if(GPIO_Pin==GPIO_PIN_7){

		BaseType_t woken=pdFALSE;
		vTaskNotifyGiveFromISR(taskHandle,&woken);
		portYIELD_FROM_ISR(woken);

	}



}


/* Kada se jednom klikne dugme aktivira se task koji ide da odredi kliknuto dugme.
 * Kada odredi stavi se flag da je dugme kliknuto i startuje se timer
 * koji provreva da li je dugme kliknuto.. Dokle god je kliknuto timer se iznova aktiira..
 * kad se otpusti stavi se flag da kada se klikne taster opet moze da racuna koji je kliknut
 */


