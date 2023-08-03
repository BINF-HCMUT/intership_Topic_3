/*
 * GPIO.h
 *
 *  Created on: Jul 24, 2023
 *      Author: Acer
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#include "main.h"
#include "global.h"

void ledMode(GPIO_TypeDef *GPIOx, uint16_t pin );
void ledStatus(GPIO_TypeDef *GPIOx, uint16_t pin, uint8_t PinState);
void buttonMode(GPIO_TypeDef *GPIOx, uint16_t pin);
void pwmMode(TIM_HandleTypeDef *htim, uint8_t indexTim, uint8_t indexChannel, uint32_t prescaler, uint32_t period);
void checkGPIO(uint8_t indexTim, uint8_t indexChannel);
void deleteGPIO(uint8_t indexTim, uint8_t indexChannel);
#endif /* INC_GPIO_H_ */
