/*
 * work.c
 *
 *  Created on: Jan 25, 2021
 *      Author: dukak
 */




#include "FreeRTOS.h"
#include "task.h"

#include "string.h"
#include "uart_driver.h"
#include "work.h"

uint8_t velocity[2]={0,0};


void static workTask(void* par){


	while(1){

		UART_BlockTxString(VT,"Unesite komandu: ");

char* input=UART_BlockRxString(VT);

if((input[0]!='1' && input[0]!='2') || (input[1]!='i' && input[1]!='d')){



UART_BlockTxString(VT,"Error\r");



}else{
	UART_BlockTxString(VT,"Uspesno uneta komanda! \r ");

	uint8_t motor;

	motor=input[0]-'0';
	if(input[1]=='i'){
		if(velocity[motor]<16)
		velocity[motor]++;

	}else if(input[1]=='d'){
		if(velocity[motor]>0)
		velocity[motor]--;

	}
	MotorCommand motorCommand =
				{ .motor = motor, .velocity = velocity[motor] };

UART_MotorCommandTx(MCU,motorCommand);


}


vPortFree(input);
}





}





void work_Init(){
	UART_Init();
xTaskCreate(workTask,"workTask",128,NULL,5,NULL);



}








