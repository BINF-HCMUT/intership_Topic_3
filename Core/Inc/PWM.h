/*
 * PWM.h
 *
 *  Created on: Aug 2, 2023
 *      Author: admin
 */

#ifndef INC_PWM_H_
#define INC_PWM_H_
#include "main.h"
#define prescaler	48
#define counterPeriod	100
extern TIM_HandleTypeDef htim1;


void PWM_Init();


#endif /* INC_PWM_H_ */
