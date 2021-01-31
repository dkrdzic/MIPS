

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



#define SCB ((SCB_RegisterMemoryMapType*) 0xE000ED00)

#define SCB_SHCSR_USGFAULTENA (1<<18)
#define SCB_SHCSR_BUSFAULTENA (1<<17)
#define SCB_SHCRSP_MEMFAULTENA (1<<16)

#define SCB_NMIPENDSET (1<<31)
#define SCB_PENDSVSET (1<<28)
#define SCB_PENDSVCLR (1<<27)
#define SCB_PENDSTSET (1<<26)
#define SCB_PENDSTCLR (1<<25)





#endif









