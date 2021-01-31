

#ifndef _SCB_H_

#define _SCB_H_


#include <stdint.h>

typedef struct{

	uint32_t CPUID;
	uint32_t ICSR;
	uint32_t VTOR;
	uint32_t AIRCR;
	uint32_t SCR;
	uint32_t CCR;
	uint32_t SHPR[3];
	uint32_t SHCSR;
	uint32_t CFSR;
	uint32_t HFSR;
	uint32_t dummy;
	uint32_t MMAR;
	uint32_t BFAR;



}SCB_RegisterMemoryMapType;





#define SCB 	((SCB_RegisterMemoryMapType*)  0xE000ED00)






#endif






