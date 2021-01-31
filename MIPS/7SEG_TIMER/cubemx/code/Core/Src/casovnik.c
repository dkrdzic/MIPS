/*
 * casovnik.c
 *
 *  Created on: Nov 30, 2020
 *      Author: dukak
 */


#include "main.h"
#include "tim.h"
#include "gpio.h"
#include "casovnik.h"





uint8_t seven_seg[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};

uint8_t digit1[]={1,2,3,4};
uint8_t digit2[]={0,0,0,0};
uint32_t tek=0;
uint32_t v=0;
void casovnik(){


	//faza 1.. Anode imaju 1 izlaz na koji se dovodiisti napon..
	//to mozemo kada hocemo jednu istu vrednost na sva 4 displeja
/*
	GPIOC->ODR&=0xFFFFFF00;
GPIOC->ODR|=seven_seg[8];
*/



	//faza 2
	//displej treba prikazati 4 razlicite cifre, na svakom displeju druga cifra u isto vreme
	//za to nam treba timer jer je ne moguce da u oisto vreme sva 4 displeja
	//prikazuju razl vrednost, vec je moguce simulirati to tako sto se
	//u kratkim vrem treucima prikazuje vrednost na razl displeju i tako dobijamo privid
/*
HAL_TIM_Base_Start(&htim1);
for(;;){

	while((TIM1->SR&&1)==0){


	}

	GPIOC->ODR&=0xFFFFF0FF;
	GPIOC->ODR&=0xFFFFFF00;
	GPIOC->ODR|=seven_seg[digit1[tek]];
	GPIOC->ODR|=(1<<(8+tek));
	tek=(tek+1)%4;
	TIM1->SR&=~1;
}
*/


	//faza 4
	//HAL_TIM_Base_Start_IT(&htim1);

//moj zadatak.. kad se klikne dugme na PB0 inc displej..

	GPIOC->ODR&=0xFFFFF0FF;

	GPIOC->ODR&=0xFFFFFF00;
	GPIOC->ODR|=seven_seg[v];

	GPIOC->ODR|=(1<<(tek+8));
	tek=(tek+1)%4;

}

uint32_t cnt=0;
uint32_t min=0;
uint32_t sek=0;


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){


if (htim->Instance==htim1.Instance){

	if(++cnt==100){
		cnt=0;
		if(++sek==60){
			sek=0;
			if(++min==60){
				min=0;

			}

		}


	}

	digit2[0]=min/10;
	digit2[1]=min%10;
	digit2[2]=sek/10;
	digit2[3]=sek%10;


	GPIOC->ODR&=0xFFFFF0FF;

	GPIOC->ODR&=0xFFFFFF00;
	GPIOC->ODR|=seven_seg[digit2[tek]];

	GPIOC->ODR|=(1<<(tek+8));
	tek=(tek+1)%4;

}


}

uint32_t exti=8;
uint8_t last=0;
uint8_t inc=0;
uint8_t dec=0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){


//faza 4.. resetuj timer
	/*
HAL_TIM_Base_Stop_IT(&htim1);

digit2[0]=0;
digit2[1]=0;
digit2[2]=0;
digit2[3]=0;
cnt=0;
min=0;
sek=0;

HAL_TIM_Base_Start_IT(&htim1);
*/

//moj zad


	if(GPIO_Pin==GPIO_PIN_0){

		if(dec)tek=(last+1)%4;

	GPIOC->ODR&=0xFFFFF0FF;

	GPIOC->ODR&=0xFFFFFF00;
	GPIOC->ODR|=seven_seg[++v];

	GPIOC->ODR|=(1<<(tek+8));
	last=tek;
	tek=(tek+1)%4;

	inc=1;
	dec=0;
	}else if(GPIO_Pin==GPIO_PIN_9){
if(inc)tek=(last-1)%4;
		GPIOC->ODR&=0xFFFFF0FF;

		GPIOC->ODR&=0xFFFFFF00;
		GPIOC->ODR|=seven_seg[--v];

		GPIOC->ODR|=(1<<(8+tek));
		last=tek;
		tek=(tek-1)%4;
dec=1;
inc=0;



	}


}










