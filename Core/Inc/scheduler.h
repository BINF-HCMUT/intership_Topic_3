/*

 * scheduler.h
 *
 *  Created on: Jun 21, 2023
 *      Author: Acer


#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "main.h"
#include <stdint.h>

typedef struct {
	void (*pTask)(void);
	uint32_t Delay;
	uint32_t Period;
	uint8_t RunMe;
    struct sTask *pNext;
	uint32_t TaskID;
}sTask;

#define SCH_MAX_TASKS 40
#define NO_TASK_ID 0

void SCH_Init(void);

unsigned char SCH_Add_Task(void(*pFunction)(), uint32_t DELAY, uint32_t PERIOD);

void SCH_Update(void);

void SCH_Dispatch_Tasks(void);

void SCH_Delete_Task(const unsigned char INDEX);

#endif  INC_SCHEDULER_H_
*/
#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_
#include "stdint.h"

typedef struct{
	void (*pTask)(void);
	uint32_t 	Delay;
	uint32_t 	Period;
	uint8_t 	RunMe;

	uint32_t 	TaskID;
}sTasks;

#define SCH_MAX_TASKS	40
void SCH_Add_Task ( void (*pFunction)() ,
					uint32_t DELAY,
					uint32_t PERIOD);

void SCH_Update(void);

void SCH_Dispatch_Tasks(void);

void SCH_pressButton(uint8_t index);

void Timer_init();
void Watchdog_init();
#endif /* INC_SCHEDULER_H_ */
