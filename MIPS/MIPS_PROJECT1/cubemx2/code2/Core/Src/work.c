/*
 * work.c
 *
 *  Created on: Jan 28, 2021
 *      Author: dukak
 */


#include "FreeRTOS.h"
#include "task.h"
#include "work.h"
#include "uart_driver.h"
#include "tim.h"
#include "lcd.h"
#include "keypad.h"

static void workTask(void* par){

send(Instruction,0x80);
send(Data,'a');
send(Instruction,0x40);
send(Data,0x1F);
send(Data,0x1F);
send(Data,0x1F);
send(Data,0x1F);
send(Data,0x1F);
send(Data,0x1F);
send(Data,0x1F);

	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
	htim3.Instance->CCR1=0;
	htim3.Instance->CCR2=0;


	while(1){


		MotorCommand  mc=receiveMotorCommand();

		if(mc.motor==1){
			htim3.Instance->CCR1=mc.velocity;
			send(Instruction,0x80);

		}else if(mc.motor==2){
			send(Instruction,0xC0);
			htim3.Instance->CCR2=mc.velocity;

		}

uint32_t i=0;
while(i<16){

	if(i<mc.velocity) send(Data,0x00);
	else send(Data, ' ');
i++;
}

	}



	}








void work_Init(){
	KEYPAD_Init();
	UART_Init();
	LCD_Init();
	xTaskCreate(workTask,"workTask",64,NULL,5,NULL);



}
