


#ifndef _STK_H_
#define _STK_H_



#include <stdint.h>


typedef struct{

	uint32_t CTRL;
	uint32_t LOAD;
	uint32_t VAL;
	uint32_t CALIB;



}STK_RegisterMemoryMapType;


#define STK ((STK_RegisterMemoryMapType*) 0xE000E010)


#endif


