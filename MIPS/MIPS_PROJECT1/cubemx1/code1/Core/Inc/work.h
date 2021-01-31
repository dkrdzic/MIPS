/*
 * work.h
 *
 *  Created on: Jan 28, 2021
 *      Author: dukak
 */

#ifndef CORE_INC_WORK_H_
#define CORE_INC_WORK_H_


typedef struct{

	uint8_t motor;
	uint8_t velocity;

}MotorCommand;


void work_Init();
#endif /* CORE_INC_WORK_H_ */
