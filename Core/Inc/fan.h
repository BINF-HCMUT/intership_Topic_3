/*
 * fan.h
 *
 *  Created on: Jul 24, 2023
 *      Author: admin
 */

#ifndef INC_FAN_H_
#define INC_FAN_H_

#include "main.h"
extern TIM_HandleTypeDef htim1;

void setFan(uint8_t dutyCycle);
void resetFan(void);

#endif /* INC_FAN_H_ */
