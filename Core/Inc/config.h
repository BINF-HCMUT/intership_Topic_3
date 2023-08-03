/*
 * config.h
 *
 *  Created on: Aug 3, 2023
 *      Author: Acer
 */

#ifndef INC_CONFIG_H_
#define INC_CONFIG_H_

#include "main.h"
#include "global.h"

void ledMode(GPIO_TypeDef *GPIOx, uint16_t pin );
void ledStatus(GPIO_TypeDef *GPIOx, uint16_t pin, uint8_t PinState);
void buttonMode(GPIO_TypeDef *GPIOx, uint16_t pin);
void pwmMode(TIM_HandleTypeDef *htim, uint8_t indexTim, uint8_t indexChannel, uint32_t prescaler, uint32_t period);
void checkGPIO(uint8_t indexTim, uint8_t indexChannel);
void deleteGPIO(uint8_t indexTim, uint8_t indexChannel);
void ADC_Config(ADC_HandleTypeDef *hadc, uint8_t index);
void ADC_MspInit(ADC_HandleTypeDef* adcHandle);

#endif /* INC_CONFIG_H_ */
