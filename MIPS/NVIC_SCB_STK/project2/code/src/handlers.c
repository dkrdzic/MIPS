


#include <stdint.h>
#include "nvic.h"

extern uint32_t bss;

void systick_handler(){

	bss++;


}



void pendSV_handler(){}


void irq0_handler(){


	//3)
	//NVIC->ISPR[0]=0x02;
	//NVIC->ISPR[0]=0x04;
}


void irq1_handler(){

	// NVIC->ICPR[0]=1;
}


void irq2_handler(){}
