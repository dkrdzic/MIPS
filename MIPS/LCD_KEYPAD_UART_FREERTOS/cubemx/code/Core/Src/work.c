/*
 * work.c
 *
 *  Created on: Jan 17, 2021
 *      Author: dukak
 */


#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "lcd.h"
#include "gpio.h"
#include "key.h"
#include "uart.h"




static void work_Task(void* param){

/*
	char string[15]="Dule Car!!!";

	send(Instruction,0x80);
	for(int i=0;i<10;i++){

		send(Data,string[i]);
		vTaskDelay(100);
	}

	send(Instruction,0x0F);
	send(Instruction, 0xC4);
	vTaskDelay(1000);
	send(Instruction,0x10);
vTaskDelay(1000);

send(Instruction,0x40);
send(Data,0x04);// _ _ _ _
send(Data,0x02);// _ _ _ _
send(Data,0x09);// _ _ _ _
send(Data,0x01);// _ _ _ _
send(Data,0x09);// _ _ _ _
send(Data,0x02);// _ _ _ _
send(Data,0x04);// _ _ _ _
send(Instruction,0xC5);
send(Data,0x00);
*/

transmitChar('a');
transmitChar('\r');

send(Instruction,0x80);

while(1){

	char a=receiveChar();

    if(a==13)
		send(Instruction,0xC0);
	else if(a==8) {
		send(Instruction,0x10);
		send(Data,' ');
		send(Instruction,0x10);


	}else{

		send(Data,a);

	}

}



}




void workInit(){
	LCD_Init();
	UART_Init();
	//KEY_Init();

	xTaskCreate(work_Task,"lcd_task",128,NULL,5,NULL);

}





