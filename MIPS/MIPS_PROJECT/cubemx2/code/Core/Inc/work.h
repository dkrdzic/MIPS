/*
 * work.h
 *
 *  Created on: Jan 26, 2021
 *      Author: dukak
 */

#ifndef CORE_SRC_WORK_H_
#define CORE_SRC_WORK_H_



typedef struct{

	uint8_t motor;
	uint8_t velocity;

}MotorCommand;



void work_Init();

#endif /* CORE_SRC_WORK_H_ */
