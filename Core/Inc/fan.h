/*
 * fan.h
 *
 *  Created on: Aug 8, 2023
 *      Author: Acer
 */

#ifndef INC_FAN_H_
#define INC_FAN_H_

#include "main.h"
extern TIM_HandleTypeDef htim3;

void setFan(uint8_t dutyCycle);
void resetFan(void);


#endif /* INC_FAN_H_ */
