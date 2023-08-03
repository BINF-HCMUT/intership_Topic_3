/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */
uint16_t gpio_PIN[16] = {
		0x0001,  /* Pin 0 selected    */
		0x0002,  /* Pin 1 selected    */
		0x0004,  /* Pin 2 selected    */
		0x0008,  /* Pin 3 selected    */
		0x0010,  /* Pin 4 selected    */
		0x0020,  /* Pin 5 selected    */
		0x0040,  /* Pin 6 selected    */
		0x0080,  /* Pin 7 selected    */
		0x0100,  /* Pin 8 selected    */
		0x0200,  /* Pin 9 selected    */
		0x0400,  /* Pin 10 selected    */
		0x0800,  /* Pin 11 selected    */
		0x1000,  /* Pin 12 selected    */
		0x2000,  /* Pin 13 selected    */
		0x4000,  /* Pin 14 selected    */
		0x8000  /* Pin 15 selected    */
};
/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */
void Set_Pin_Output(GPIO_TypeDef  *GPIOx,uint16_t pin){
	/* Check GPIOx parameter */
	assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
	/* Check pin parameter */
	assert_param(IS_GPIO_PIN(gpio_PIN[pin]));
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOx, gpio_PIN[pin], GPIO_PIN_RESET);

	/*Configure GPIO pin */
	GPIO_InitStruct.Pin = gpio_PIN[pin];
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void Set_Pin_Input(GPIO_TypeDef  *GPIOx,uint16_t pin){
	/* Check GPIOx parameter */
	assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
	/* Check pin parameter */
	assert_param(IS_GPIO_PIN(gpio_PIN[pin]));
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOx, gpio_PIN[pin], GPIO_PIN_RESET);

	/*Configure GPIO pin */
	GPIO_InitStruct.Pin = gpio_PIN[pin];
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}
void ledStatus(GPIO_TypeDef  *GPIOx,uint16_t pin,uint8_t PinState){
	/* Check GPIOx parameter */
	assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
	/* Check pin parameter */
	assert_param(IS_GPIO_PIN(gpio_PIN[pin]));
	/* Check pinState parameter */
	assert_param(IS_GPIO_PIN_ACTION(PinState));

	HAL_GPIO_WritePin(GPIOx, gpio_PIN[pin], PinState);
}
/* USER CODE END 2 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
