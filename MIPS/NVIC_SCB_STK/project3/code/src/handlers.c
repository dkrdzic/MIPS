

#include "nvic.h"


void nmi_handler(){}


void hf_handler(){}

void uf_handler(){}

void svc_handler(){}

void pendSV_handler(){}

void systick_handler(){}


void irq0_handler(){

	NVIC->ISPR[0]=0x02;
	NVIC->ISPR[0]=0x04;


}

void irq1_handler(){}

void irq2_handler(){}





