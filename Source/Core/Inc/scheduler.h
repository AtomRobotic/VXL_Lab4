/*
 * scheduler.h
 *
 *  Created on: Nov 26, 2024
 *      Author: ADMIN
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include <stdint.h>
#include "main.h"

typedef struct {
	// Pointer to the task (must be a ’void (void) ’ function)
	void ( * pTask)(void) ;
	// Delay (ticks) until the function will (next) be run
	uint32_t Delay;
	// Interval (ticks) between subsequent runs.
	uint32_t Period;
	// Incremented (by scheduler) when task is due to execute
	uint8_t RunMe;
	//This is a hint to solve the question below.
	uint32_t TaskID;
} sTask;

#define SCH_MAX_TASKS	10

void SCH_Init(void);
void SCH_Update(void);
unsigned char SCH_Add_Task(void (* pFunction) () , unsigned int DELAY, unsigned int PERIOD);
void SCH_Dispatch_Tasks(void);
void SCH_Shift_Task(const int TASK_INDEX);
unsigned char SCH_Delete_Task(const int TASK_INDEX);



#endif /* INC_SCHEDULER_H_ */
