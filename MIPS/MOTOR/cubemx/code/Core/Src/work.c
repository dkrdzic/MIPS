/*
 * work.c
 *
 *  Created on: Dec 10, 2020
 *      Author: dukak
 */

#include "main.h"
#include "tim.h"
#include "gpio.h"

uint16_t ccr=0;


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){

if(GPIO_Pin==GPIO_PIN_0){

if(ccr<15){


	ccr=++TIM1->CCR1;

}

}
else if(GPIO_Pin==GPIO_PIN_1){

	if(ccr>0){
	ccr=--TIM1->CCR1;
	}
}
}
