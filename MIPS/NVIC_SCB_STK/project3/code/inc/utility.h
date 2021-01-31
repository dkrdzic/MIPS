

#ifndef _UTILITY_H_
#define _UTILITY_H_


#include <stdint.h>


#define SET_VALUE(target,bitStartIncl,bitEndIncl,value)\
	do{\
	uint32_t temp=(target);\
	uint32_t mask=~(~0<<((bitEndIncl)-(bitStartIncl)+1));\
	temp&=~(mask<<(bitStartIncl));\
	temp|=(mask & (value))<<(bitStartIncl);\
	(target)=temp;\
	}while(0)





#endif










