/*
 * stoperica.c
 *
 *  Created on: Dec 6, 2020
 *      Author: dukak
 */


#include "main.h"
#include "tim.h"
#include "gpio.h"

uint16_t data=8;
uint32_t b=9;

uint8_t seven_seg[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};

uint8_t cnt,tek=0;

uint8_t digit[]={0,0};


void stoperica(){




}






void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){


if(htim->Instance==htim1.Instance){



	if(data>0){

		if(++cnt==100){
			cnt=0;
			data--;


		}
	digit[0]=data/10;
	digit[1]=data%10;


GPIOC->ODR&=0xFFFFF0FF;
GPIOC->ODR&=0xFFFFFF00;
GPIOC->ODR|=seven_seg[digit[tek]];
GPIOC->ODR|=(1<<(tek+10));
tek=(tek+1)%2;

	}
	else{




	GPIOC->ODR&=0xFFFFF0FF;
	GPIOC->ODR&=0xFFFFFF00;
	GPIOC->ODR|=seven_seg[0];
	GPIOC->ODR|=(1<<(tek+10));
	tek=(tek+1)%2;


	}


}



}



void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){

data=GPIOB->IDR;
b=GPIOB->IDR;
data&=0x001F;

HAL_TIM_Base_Start_IT(&htim1);


}


