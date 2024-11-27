/*
 * scheduler.c
 *
 *  Created on: Nov 26, 2024
 *      Author: ADMIN
 */

/* Ý tưởng:
 *
 * */

#include "scheduler.h"

sTask SCH_tasks_G[SCH_MAX_TASKS];
uint8_t task_count = 0;

void SCH_Init(void){
	task_count = 0;
	unsigned char i ;
	 for (i = 0; i <SCH_MAX_TASKS; i++) {
		 SCH_Delete_Task(i);
	 }
}

void SCH_Update(void){
	 // Check if there is a task at this location
	 if (SCH_tasks_G[0].pTask){
		 if (SCH_tasks_G[0].Delay == 0) {
			 // The task is due to run
			 // Inc. the ’RunMe’ flag
			 SCH_tasks_G[0].RunMe += 1;
			 if (SCH_tasks_G[0].Period) {
				 // Schedule periodic tasks to run again
				 SCH_tasks_G[0].Delay = SCH_tasks_G[0].Period;
			 }
		 } else {
			 // Not yet ready to run: just decrement the delay
				SCH_tasks_G[0].Delay -= 1;
		 }
	 }
}

unsigned char SCH_Add_Task(void (* pFunction) () , unsigned int DELAY, unsigned int PERIOD){
	unsigned char Index = 0;
	if(task_count == 0){
		// Add task at the index = 0 if the scheduler is empty
		SCH_tasks_G[0].pTask = pFunction;
		SCH_tasks_G[0].Delay = DELAY;
		SCH_tasks_G[0].Period = PERIOD;
		SCH_tasks_G[0].RunMe = 0;
		task_count++;
	}else if(task_count > 0){
		while((Index < task_count) && (task_count < SCH_MAX_TASKS)){
			if(SCH_tasks_G[Index].Delay > DELAY){
				for(int i  = task_count; i > Index; i--){
					SCH_tasks_G[i] = SCH_tasks_G[i-1];
				}
				SCH_tasks_G[Index].pTask = pFunction;
				SCH_tasks_G[Index].Delay = DELAY;
				SCH_tasks_G[Index].Period = PERIOD;
				SCH_tasks_G[Index].RunMe = 0;
				task_count++;
				for(int j = Index + 1; j < task_count; j++){
					SCH_tasks_G[j].Delay -= DELAY;
				}
				break;
			}else{
				DELAY -= SCH_tasks_G[Index].Delay;
			}
			Index++;
		}
		if((Index == task_count) && (task_count + 1 < SCH_MAX_TASKS)){
			SCH_tasks_G[Index].pTask = pFunction;
			SCH_tasks_G[Index].Delay = DELAY;
			SCH_tasks_G[Index].Period = PERIOD;
			SCH_tasks_G[Index].RunMe = 0;
			task_count++;
		}
	}
	return Index;
}

void SCH_Dispatch_Tasks(void){
	// Dispatches the next task
	if(SCH_tasks_G[0].RunMe > 0){
		(*SCH_tasks_G[0].pTask)();
		SCH_tasks_G[0].RunMe -= 1;
		// Periodic tasks will automatically run again
		// − if this is a ’one shot’ task, remove it from the array
		if(SCH_tasks_G[0].Period == 0){
			SCH_Delete_Task(0);
		}else{
			sTask temp = SCH_tasks_G[0];
			SCH_Delete_Task(0);
			SCH_Shift_Task(0);
			SCH_Add_Task(temp.pTask, temp.Delay, temp.Period);
		}
	}
}

void SCH_Shift_Task(const int TASK_INDEX){
	if(TASK_INDEX != task_count - 1){
		for(int i = TASK_INDEX; i < task_count - 1; i++){
			SCH_tasks_G[i] = SCH_tasks_G[i+1];
		}
		SCH_tasks_G[task_count - 1].pTask = 0x0000;
		SCH_tasks_G[task_count - 1].Delay = 0;
		SCH_tasks_G[task_count - 1].Period = 0;
		SCH_tasks_G[task_count - 1].RunMe = 0;
	}
	task_count--;
}

unsigned char SCH_Delete_Task(const int TASK_INDEX) {
	unsigned char flag;
	flag = 0;
	SCH_tasks_G[TASK_INDEX].pTask = 0x0000;
	SCH_tasks_G[TASK_INDEX].Delay = 0;
	SCH_tasks_G[TASK_INDEX].Period = 0;
	SCH_tasks_G[TASK_INDEX].RunMe = 0;
	return flag; // return status
}
