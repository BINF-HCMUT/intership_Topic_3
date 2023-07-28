/*
 * GPIO.c
 *
 *  Created on: Jul 24, 2023
 *      Author: Acer
 */

#include "global.h"
#include "GPIO.h"
#include "main.h"
#include "stm32f1xx_hal_gpio.h"

extern UART_HandleTypeDef huart2;

void ledMode(GPIO_TypeDef *GPIOx, uint16_t pin ){
	     GPIO_InitTypeDef GPIO_InitStruct;

	    /*Check GPIOx parameter */
	    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
	    /*Check pin parameter*/
	    assert_param(IS_GPIO_PIN(GPIO_PIN[pin]));

	    /* GPIO Ports Clock Enable */
	    __HAL_RCC_GPIOC_CLK_ENABLE();
	    __HAL_RCC_GPIOD_CLK_ENABLE();
	    __HAL_RCC_GPIOA_CLK_ENABLE();
	    __HAL_RCC_GPIOB_CLK_ENABLE();

	    /*Configure GPIO pin Output Level*/
	    HAL_GPIO_WritePin(GPIOx, GPIO_PIN[pin], RESET);

	    /*Configure GPIO pin*/
	    GPIO_InitStruct.Pin = GPIO_PIN[pin]; // Assigns the value of the pin variable to the Pin field in the GPIO_InitStruct structure
	    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;// Sets the mode of the GPIO pin as output with push-pull configuratio
	    GPIO_InitStruct.Pull = GPIO_NOPULL;// Sets the pull state of the GPIO pin to no pull
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;//Sets the speed of the GPIO pin to low-frequency speed
	    HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);//Initializes and configures the GPIO pin
}

void ledStatus(GPIO_TypeDef *GPIOx, uint16_t pin, uint8_t PinState){
	assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
	assert_param(IS_GPIO_PIN(GPIO_PIN[pin]));
	assert_param(IS_GPIO_PIN_ACTION(PinState));
	HAL_GPIO_WritePin(GPIOx, GPIO_PIN[pin], PinState);
}
 void buttonMode(GPIO_TypeDef *GPIOx, uint16_t pin){
	 GPIO_InitTypeDef GPIO_InitStruct = {0};

	  /* GPIO Ports Clock Enable */
	  __HAL_RCC_GPIOC_CLK_ENABLE();
	  __HAL_RCC_GPIOD_CLK_ENABLE();
	  __HAL_RCC_GPIOA_CLK_ENABLE();
	  __HAL_RCC_GPIOB_CLK_ENABLE();

	  /*Configure GPIO pins : Button0_Pin Button1_Pin Button2_Pin */
	  GPIO_InitStruct.Pin = GPIO_PIN[pin];
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
 }
//void MspPostInit(GPIO_TypeDef *GPIOx, uint16_t pin)
//{
//    GPIO_InitTypeDef GPIO_InitStruct;
//
//    /* GPIO Ports Clock Enable */
//    __HAL_RCC_GPIOC_CLK_ENABLE();
//    __HAL_RCC_GPIOD_CLK_ENABLE();
//    __HAL_RCC_GPIOA_CLK_ENABLE();
//    __HAL_RCC_GPIOB_CLK_ENABLE();
//
//    // Kích hoạt clock cho GPIOA
//    __HAL_RCC_GPIOA_CLK_ENABLE();
//
//    // Cấu hình chân PA2 với Alternate Function mode
//    GPIO_InitStruct.Pin =  GPIO_PIN[pin];
//    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//    GPIO_InitStruct.Pull = GPIO_PULLUP;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
////    GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
//    HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
//}

//void pwmMode(TIM_HandleTypeDef *htim, GPIO_TypeDef *GPIOx, uint16_t pin){
//	__HAL_RCC_TIM3_CLK_ENABLE();
//
//    /*Check GPIOx parameter */
//    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
//    /*Check pin parameter*/
//    assert_param(IS_GPIO_PIN(GPIO_PIN[pin]));
//
//     TIM_ClockConfigTypeDef sClockSourceConfig = {0};
//     TIM_MasterConfigTypeDef sMasterConfig = {0};
//     TIM_OC_InitTypeDef sConfigOC = {0};
//
//     /* USER CODE BEGIN TIM3_Init 1 */
//
//     /* USER CODE END TIM3_Init 1 */
//     htim->Instance = TIM3;
//     htim->Init.Prescaler = 0;
//     htim->Init.CounterMode = TIM_COUNTERMODE_UP;
//     htim->Init.Period = 89;
//     htim->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
//     htim->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
//     if (HAL_TIM_Base_Init(htim) != HAL_OK)
//     {
//       Error_Handler();
//     }
//     sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
//     if (HAL_TIM_ConfigClockSource(htim, &sClockSourceConfig) != HAL_OK)
//     {
//       Error_Handler();
//     }
//     if (HAL_TIM_PWM_Init(htim) != HAL_OK)
//     {
//       Error_Handler();
//     }
//     sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
//     sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
//     if (HAL_TIMEx_MasterConfigSynchronization(htim, &sMasterConfig) != HAL_OK)
//     {
//       Error_Handler();
//     }
//     sConfigOC.OCMode = TIM_OCMODE_PWM1;
//     sConfigOC.Pulse = 0;
//     sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
//     sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
//     if (HAL_TIM_PWM_ConfigChannel(htim, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
//     {
//       Error_Handler();
//     }
////      MspPostInit(GPIOx, pin);
//     GPIO_InitTypeDef GPIO_InitStruct;
//
//      /* GPIO Ports Clock Enable */
//      __HAL_RCC_GPIOC_CLK_ENABLE();
//
//      // Cấu hình chân PA2 với Alternate Function mode
//      GPIO_InitStruct.Pin =  GPIO_PIN[pin];
//      GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//      GPIO_InitStruct.Pull = GPIO_PULLUP;
//      GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
////      GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
//      HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
//  	  HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "!check=%s#\r\n", "OK"), 1000);
//}
