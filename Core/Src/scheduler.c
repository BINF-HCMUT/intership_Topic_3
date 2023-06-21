/*
 * scheduler.c
 *
 *  Created on: Nov 24, 2022
 *      Author: admin
 */


#include "scheduler.h"

uint8_t current_index_task = 0;
sTasks SCH_tasks_G[SCH_MAX_TASKS];

void Timer_init(){

}
void Watchdog_init(){

}



void SCH_Add_Task ( void (*pFunction)() , uint32_t DELAY, uint32_t PERIOD){
	if(current_index_task < SCH_MAX_TASKS){

		SCH_tasks_G[current_index_task].pTask = pFunction;
		SCH_tasks_G[current_index_task].Delay = DELAY / 10;
		SCH_tasks_G[current_index_task].Period =  PERIOD / 10;
		SCH_tasks_G[current_index_task].RunMe = 0;

		SCH_tasks_G[current_index_task].TaskID = current_index_task;

		current_index_task++;
	}
}

void SCH_Update(void){
	for(int i =0 ; i<current_index_task;i++){
		if(SCH_tasks_G[i].Delay > 0){
			SCH_tasks_G[i].Delay --;
		}else{
			SCH_tasks_G[i].RunMe += 1;
			SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;
		}
	}
}


void SCH_Dispatch_Tasks(void){
	for(uint32_t i = 0; i < current_index_task; i++){
		if(SCH_tasks_G[i].RunMe > 0){
			SCH_tasks_G[i].RunMe--;
			(*SCH_tasks_G[i].pTask)();
			if(SCH_tasks_G[i].Period == 0){
				SCH_Delete_Tasks(i);
			}
		}
	}
}

void SCH_Delete_Tasks(uint32_t index){
	for(int i = index; i< current_index_task;i++){
		SCH_tasks_G[i].pTask = SCH_tasks_G[i+1].pTask;
		SCH_tasks_G[i].Delay = SCH_tasks_G[i+1].Delay;
		SCH_tasks_G[i].Period= SCH_tasks_G[i+1].Period;
		SCH_tasks_G[i].RunMe = SCH_tasks_G[i+1].RunMe;

		SCH_tasks_G[i].TaskID = SCH_tasks_G[i+1].TaskID;
	}
	current_index_task--;
}


