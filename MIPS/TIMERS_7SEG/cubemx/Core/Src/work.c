/*
 * work.c
 *
 *  Created on: Dec 9, 2020
 *      Author: dukak
 */

#include "main.h"

#include "gpio.h"
#include "tim.h"




uint8_t volatile seven_seg[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};

uint8_t digit1234[]={1,2,3,4};
uint8_t volatile timer[]={0,0,0,0};

uint8_t volatile tek=0;
uint8_t volatile counter=0;
uint8_t volatile sek=0;
uint8_t volatile min=0;

typedef enum {

	WAIT_RE,WAIT_PERIOD_END
}State;

uint16_t volatile cntStartActive=0;
uint16_t volatile cntPeriodEnd=0;
uint16_t volatile cnt=0;
uint32_t volatile f=0;
uint8_t showFreq=0;

State volatile state=WAIT_RE;

uint32_t overflowCounter=0;


void setGPIOB(uint16_t GPIO_PIN, GPIO_PinState GPIO_PIN_STATE){

if(GPIO_PIN>=GPIO_PIN_12 && GPIO_PIN<=GPIO_PIN_15){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN,GPIO_PIN_STATE);

}


}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){

	if(GPIO_Pin==GPIO_PIN_11){
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_12);

		min=0;
		sek=0;
		counter=0;
		showFreq=0;

	}
	else if(GPIO_Pin==GPIO_PIN_10){

		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_12);
		showFreq=1;
	}




}
void showFrequency(){

	showFreq=1;

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){

overflowCounter++;
	if (htim->Instance==TIM1){

//3
		/*
		GPIOC->ODR&=0xFFFFF0FF;
		GPIOC->ODR&=0xFFFFFF00;
		GPIOC->ODR|=seven_seg[digit1234[tek]];
		GPIOC->ODR|=(1<<(tek+8));
		tek=(tek+1)%4;
*/

		//4

if(showFreq==0){
		if(++counter==100){
counter=0;
if(++sek==60){
	sek=0;
	if(++min==60)min=0;

}

		}

		timer[0]=min/10;
		timer[1]=min%10;
		timer[2]=sek/10;
		timer[3]=sek%10;

		GPIOC->ODR&=0xFFFFF0FF;
			GPIOC->ODR&=0xFFFFFF00;
			GPIOC->ODR|=seven_seg[timer[tek]];
			GPIOC->ODR|=(1<<(tek+8));
			tek=(tek+1)%4;

	}

else{

	timer[0]=f/1000%10;
			timer[1]=f/100%10;
			timer[2]=f/10%10;
			timer[3]=f%10;

			GPIOC->ODR&=0xFFFFF0FF;
				GPIOC->ODR&=0xFFFFFF00;
				GPIOC->ODR|=seven_seg[timer[tek]];
				GPIOC->ODR|=(1<<(tek+8));
				tek=(tek+1)%4;
}
	}



}





void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){


	switch(state){


	case WAIT_RE:
		if(htim->Instance==TIM1 && htim->Channel==HAL_TIM_ACTIVE_CHANNEL_1){


			cntStartActive=HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_1);
			overflowCounter=0;

			state=WAIT_PERIOD_END;


		}

		break;

	case WAIT_PERIOD_END:

		if(htim->Instance==TIM1 && htim->Channel==HAL_TIM_ACTIVE_CHANNEL_1){

			cntPeriodEnd=HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_1);

cnt=(cntPeriodEnd+overflowCounter*80)-cntStartActive;
f=((8000*1000)/cnt);
overflowCounter=0;
cntStartActive=cntPeriodEnd;

			}


		break;




	}




}



















