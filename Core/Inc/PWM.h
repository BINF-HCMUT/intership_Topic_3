/*
 * PWM.h
 *
 *  Created on: Aug 2, 2023
 *      Author: admin
 */

#ifndef INC_PWM_H_
#define INC_PWM_H_
#include "main.h"

void PWM_Init(TIM_HandleTypeDef *htim,uint16_t prescaler, uint16_t counterPeriod);


#endif /* INC_PWM_H_ */
