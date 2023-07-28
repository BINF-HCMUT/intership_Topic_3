/*
 * GPIO.h
 *
 *  Created on: Jul 24, 2023
 *      Author: Acer
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#include "main.h"

void ledMode(GPIO_TypeDef *GPIOx, uint16_t pin );
void ledStatus(GPIO_TypeDef *GPIOx, uint16_t pin, uint8_t PinState);
void buttonMode(GPIO_TypeDef *GPIOx, uint16_t pin);
//void pwmMode(TIM_HandleTypeDef *htim, GPIO_TypeDef *GPIOx, uint16_t pin);
//void MspPostInit(GPIO_TypeDef *GPIOx, uint16_t pin);
#endif /* INC_GPIO_H_ */
