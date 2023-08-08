/*
 * PWM_Fan.h
 *
 *  Created on: Aug 8, 2023
 *      Author: Acer
 */

#ifndef INC_PWM_FAN_H_
#define INC_PWM_FAN_H_

#include "main.h"
#define prescaler	72
#define counterPeriod	99
extern TIM_HandleTypeDef htim3;


void PWM_FAN_Init();

#endif /* INC_PWM_FAN_H_ */
