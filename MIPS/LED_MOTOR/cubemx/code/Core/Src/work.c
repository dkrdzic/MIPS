/*
 * work.c
 *
 *  Created on: Dec 10, 2020
 *      Author: dukak
 */

#include "main.h"
#include "gpio.h"

uint8_t volatile pushed=0;
uint16_t volatile ccr=0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){

if (GPIO_Pin==GPIO_PIN_10 && pushed==0){

	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
	pushed=1;

}else if(GPIO_Pin==GPIO_PIN_11){

	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);


}else if(GPIO_Pin==GPIO_PIN_0){

	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_3);

}
else if(GPIO_Pin==GPIO_PIN_10 && pushed==1){

	pushed=0;

}
else if(GPIO_Pin==GPIO_PIN_1){

	if(TIM1->CCR1<9){
		TIM1->CCR1++;
		ccr=TIM1->CCR1;

	}


}else if(GPIO_Pin==GPIO_PIN_2){

	if(TIM1->CCR1>0){
		TIM1->CCR1--;
		ccr=TIM1->CCR1;

	}

}


}
