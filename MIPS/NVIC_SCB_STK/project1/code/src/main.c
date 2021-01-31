

#include <stdint.h>

#include "scb.h"
#include "utility.h"
#include "systick.h"
#include "nvic.h"

uint8_t const rodata[]={1,2,3,4,5};

uint8_t data[]={10,11,12,13};


uint32_t bss;


void init_systick(){

STK->LOAD=4000000-1;
STK->CTRL |=0x07;


}



uint32_t main(){



	/*
	//d)
	SCB->SHCSR |=SCB_SHCRSP_MEMFAULTENA | SCB_SHCSR_BUSFAULTENA | SCB_SHCSR_USGFAULTENA;

	SCB->ICSR|=SCB_PENDSTSET | SCB_PENDSVSET;


	SET_VALUE(SCB->AIRCR,8,10,3);
    SET_VALUE(SCB->SHPR[2],24,31,0x00);
	SET_VALUE(SCB->SHPR[0],0,7,0x10);
	SET_VALUE(SCB->SHPR[0],8,15,0x20);
	SET_VALUE(SCB->SHPR[0],16,23,0x30);
    SET_VALUE(SCB->SHPR[1],24,31,0x40);
    SET_VALUE(SCB->SHPR[2],16,23,0x50);

	SCB->ICSR|=SCB_PENDSTSET | SCB_PENDSVSET;
*/




	/*
//dj)
	init_systick();

	while(1){}
*/

	/*
	//e)

	NVIC->ISER[0]=0x07;

	SET_VALUE(SCB->AIRCR,8,10,5); //stavljam podgrupu 5 jer onda kao grupa svi imaju isti prioritet
										//ovde 00 (00..xx).. Vrednost potprioriteta
										 // ce odrediti koji ce se pre izvrsiti kada u isto vreme stignu zahtevi
										 //podgrupa xx se samo gleda kad zahtevi dodju istovremeno
										 //ako se ode u zahtev nece biti ugnezdavanja jer imaju isti prioritet
	SET_VALUE(NVIC->IPR[0],0,7,0x30);
	SET_VALUE(NVIC->IPR[0],8,15,0x10);
	SET_VALUE(NVIC->IPR[0],16,23,0x20);

	NVIC->ISPR[0]|=0x07;
*/




	//vezbanje

/*

	NVIC->ISER[0]=0x07;
	SET_VALUE(SCB->AIRCR,8,10,3);
	SET_VALUE(NVIC->IPR[0],0,7,0x30);
	SET_VALUE(NVIC->IPR[0],8,15,0x10);
	SET_VALUE(NVIC->IPR[0],16,23,0x20);

	NVIC->ISPR[0]=0x07;
*/

//prigroup=5 znaci da se deli yy..xx.. yy je prioritet prekida
// xx je potprioritet i dolaazi do izrazaja samo kad su 2 prekida sa istom grupom yy
//stigli u isto vreme



	//faultmask

	/*
	SCB->ICSR |=SCB_NMIPENDSET | SCB_PENDSTSET | SCB_PENDSVSET;

	__asm__(
			"mov r0,1 \n"
			"msr faultmask,r0"
	);

	SCB->ICSR |=SCB_NMIPENDSET | SCB_PENDSTSET | SCB_PENDSVSET;
*/


//basepri
/*
	__asm__(
			"mov r0,0x20 \n"
			"msr basepri,r0"

	);
	NVIC->ISPR[0]=0x07;
*/

/*
__asm__(

		"mov r0,1 \n"
		"msr primask, r0"

);

	SCB->ICSR|=SCB_PENDSTSET|SCB_NMIPENDSET;



	__asm__(

			"mov r0,0 \n"
			"msr primask, r0"

	);

		__asm__(
				"mov r0,1 \n"
				"msr control,r0"
		);


__asm__(
		"svc 0"
);

*/

	SCB->CCR=(1<<4);
SCB->SHCSR=(1<<18);

	int dummy0=6;
	int dummy1=dummy0/0;



	return 0;

}









