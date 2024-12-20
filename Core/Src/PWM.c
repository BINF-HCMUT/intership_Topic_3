/*
 * PWM.c
 *
 *  Created on: Aug 2, 2023
 *      Author: admin
 */


#include "PWM.h"

void PWM_Init(){
		// Enable GPIOA clock
	    __HAL_RCC_GPIOA_CLK_ENABLE();

	    // Enable Timer 1 clock
	    __HAL_RCC_TIM1_CLK_ENABLE();

	    // Configure PA8 in alternate function mode
	    GPIO_InitTypeDef GPIO_InitStruct = {0};
	    GPIO_InitStruct.Pin = GPIO_PIN_8;
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	    // Initialize Timer 1
	    htim1.Instance = TIM1;
	    htim1.Init.Prescaler = prescaler - 1;
	    htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
	    htim1.Init.Period = counterPeriod - 1;
	    htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	    HAL_TIM_Base_Init(&htim1);

	    // Configure Timer 1 channel 1 in PWM mode 1
	    TIM_OC_InitTypeDef sConfigOC = {0};
	    sConfigOC.OCMode = TIM_OCMODE_PWM1;
	    sConfigOC.Pulse = 0;
	    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	    HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1);

	    // Start PWM output on Timer 1 channel 1
	    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
}

