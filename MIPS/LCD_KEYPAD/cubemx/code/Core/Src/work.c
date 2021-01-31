/*
 * work.c
 *
 *  Created on: Jan 10, 2021
 *      Author: dukak
 */

#include "lcd.h"
#include "work.h"
#include "FreeRTOS.h"
#include "task.h"
#include "key.h"



static void work_Task(void* par){

char line1[11]="Dule car!!!";


send(Instruction,0x80); //Saljem na koju adresu u ddram pozicioniram kursor => 00;

for(uint32_t i=0;i<11;i++){

	send(Data,line1[i]);
	vTaskDelay(100);

}//saljem podatke na izlaz

vTaskDelay(1000);

send(Instruction,0x0E); //ukljuci cursor (Display On/Of control)


send(Instruction,0xC0);
for(uint32_t i=0;i<11;i++){

	send(Data,line1[i]);
	vTaskDelay(100);

}//saljem podatke na izlaz

vTaskDelay(1000);

send(Instruction,0x0F);//ukljucivanje blinkanja (Display On/Of control)

vTaskDelay(1000);

send(Instruction,0x83);//DDRAM instruction
						//da blinka karakter na adtresi 3, tj 4. po redu jer ide od 0 adresa
						//pozicioniram kursor na adresu 3

vTaskDelay(1000);

for(uint32_t i=0;i<4;i++){

	send(Instruction,0x14);//Cursor or display shift instruction

} //pomeri kursor za 4 mesta u desno


vTaskDelay(1000);

send(Instruction,0x48);//CGRAM
send(Data,0x04);    //   _ 1 _ _
send(Data,0x02);    //   _ _ 1 _
send(Data,0x09);    //   1 _ _ 1
send(Data,0x01);    //   _ _ _ 1
send(Data,0x09);    //   1 _ _ 1
send(Data,0x02);    //   _ _ 1 _
send(Data,0x04);    //   _ 1 _ _

send(Instruction,0xCC); //na koju adresu u DDRAM na displeyu upisujemo simbol
send(Data,0x01); //strana 19, jer smo koristili 0x80 kao pocetnu adresu za CGram

send(Data,':');
send(Data,')');

vTaskDelay(1000);

send(Instruction,0x40);
send(Data,0x06);    //   _ 1 1 _
send(Data,0x09);    //   1 _ _ 1
send(Data,0x01);    //   _ _ _ 1
send(Data,0x02);    //   _ _ 1 _
send(Data,0x04);    //   _ 1 _ _
send(Data,0x00);    //   _ _ _ _
send(Data,0x04);    //   _ 1 _ _

send(Instruction,0xCC);
send(Data,0x00);

KEY_Init();

while(1){

vTaskDelay(1000);

}


}










void work_Init(){

	LCD_Init();
	xTaskCreate(work_Task,"workTask",128,NULL,5,NULL);

}
