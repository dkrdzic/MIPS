

#include <stdint.h>
#include "scb.h"
#include "utility.h"
#include "stk.h"
#include "nvic.h"


uint8_t const rodata[]={1,2,3,4,5,6,7,8,9};

uint8_t data[]={10,11,12,13,14,15,16,17,18,19};

uint32_t bss;


void systick_init(){

	STK->LOAD=4000000-1;
	STK->CTRL|=0x07;


}

uint32_t main()
{

/*
	SCB->ICSR|=(1<<28)|(1<<26);
	SET_VALUE(SCB->SHPR[2],24,31,0x00);
	SET_VALUE(SCB->SHPR[2],16,23,0x10);
	SCB->ICSR|=(1<<28)|(1<<26);
*/
	/*
	systick_init();
	while(1){}
*/

	NVIC->ISER[0]=0x07;

	//NVIC->ISPR[0]=0x07;
	SET_VALUE(SCB->AIRCR,8,10,5);
	SET_VALUE(NVIC->IPR[0],0,7,0x20);
	SET_VALUE(NVIC->IPR[0],8,15,0x00);
	SET_VALUE(NVIC->IPR[0],16,23,0x10);
	//NVIC->ISPR[0]=0x07;

	NVIC->ISPR[0]=0x01;


return 0;

}











