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

uint8_t velocity[2]={0,0};

static void workTask(void* par){





	while(1){
		transmitString(VT,"Unesite komandu: ");

		char* input=receiveString(VT);


		if((input[0]=='1' || input[0]=='2') &&(input[1]=='d' || input[1]=='i')){

			uint8_t motor=input[0]-'0';

			if(input[1]=='i' && velocity[motor]<16){

				velocity[motor]++;




			}else if(input[1]=='d' && velocity[motor]>0){

				velocity[motor]--;



			}



			MotorCommand mc={motor,velocity[motor]};

				transmitMotorCommand(MCU,mc);


		}else{

			transmitString(VT,"ERROR \r ");

		}








		vPortFree(input);

	}



}




void work_Init(){
	UART_Init();
	xTaskCreate(workTask,"workTask",128,NULL,5,NULL);


}

