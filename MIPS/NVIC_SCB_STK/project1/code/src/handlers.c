

#include "scb.h"
#include "nvic.h"
#include "utility.h"

void nmi_handler(){



}


void hf_handler(){}


void mmf_handler(){}


void bf_handler(){}


void uf_handler(){}


void svcall_handler(){



	__asm__(
			"mov r0,0 \n"
			"msr control,r0"
	);

}


void pendsv_handler(){}


void systick_handler(){


}


void irq0_handler(){



}


void irq1_handler(){



}


void irq2_handler(){


	NVIC->ISPR[0]=0x01;
//NVIC->ICPR[0]=0x01;
	//NVIC->ISPR[0]=0x02;



}














