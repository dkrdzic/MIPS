/*
 * work.c
 *
 *  Created on: Jan 26, 2021
 *      Author: dukak
 */




#include "FreeRTOS.h"
#include "task.h"

#include "work.h"
#include "tim.h"
#include "uart_driver.h"
#include "lcd.h"

static void work_Task(void* par){

	send(Instruction,0x80);
	send(Data,'a');

	vTaskDelay(2000);

	send(Instruction,0x48);
	send(Data,0x1F);// _ _ _ _ _
	send(Data,0x1F);// _ _ _ _ _
	send(Data,0x1F);// _ _ _ _ _
	send(Data,0x1F);// _ _ _ _ _
	send(Data,0x1F);// _ _ _ _ _
	send(Data,0x1F);// _ _ _ _ _
	send(Data,0x1F);// _ _ _ _ _





	while(1){


//ceka komandu od MCU1
MotorCommand mc= RxMotorCommand();

if(mc.motor==1){

htim3.Instance->CCR1=mc.velocity;

send(Instruction,0x80);



}else if(mc.motor==2){

	htim3.Instance->CCR2=mc.velocity;

	send(Instruction,0xC0);




}


for(uint32_t i=0;i<16;i++){

	if(i<mc.velocity){

		send(Data,0x01);
	}else send(Data,' ');

}




	}


}














void work_Init(){

	UART_Init();
	LCD_Init();
	xTaskCreate(work_Task,"workTask",128,NULL,5,NULL);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
	htim3.Instance->CCR1 = 0;
		htim3.Instance->CCR2 = 0;
}
