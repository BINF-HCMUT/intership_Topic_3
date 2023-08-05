/*
 * config.c
 *
 *  Created on: Aug 3, 2023
 *      Author: Acer
 */

#include "global.h"
#include "config.h"
#include "main.h"
#include <stdio.h>
#include "stm32f1xx_hal_gpio.h"

extern UART_HandleTypeDef huart2;

void ledMode(GPIO_TypeDef *GPIOx, uint16_t pin ){
	static GPIO_InitTypeDef GPIO_InitStruct = {0};
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
	 static GPIO_InitTypeDef GPIO_InitStruct = {0};
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

 void pwmDMA(void){
	  /* DMA controller clock enable */
	  __HAL_RCC_DMA1_CLK_ENABLE();

	  /* DMA interrupt init */
	  /* DMA1_Channel2_IRQn interrupt configuration */
	  HAL_NVIC_SetPriority(DMA1_Channel2_IRQn, 0, 0);
	  HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn);
 }
void pwmMode(TIM_HandleTypeDef *htim, uint8_t indexTim, uint8_t indexChannel, uint32_t prescaler, uint32_t period, uint8_t dmaFlag){
	if((indexTim < 1 || indexTim > 4) || (indexChannel < 1 || indexChannel > 4)){
 	    Error_Handler();
	}
	indexTim -= 1;
	indexChannel -=1;
//	__HAL_RCC_TIM3_CLK_ENABLE();
//
//    /*Check GPIOx parameter */
//    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
//    /*Check pin parameter*/
//    assert_param(IS_GPIO_PIN(GPIO_PIN[pin]));
      TIM_ClockConfigTypeDef sClockSourceConfig = {0};
 	  TIM_MasterConfigTypeDef sMasterConfig = {0};
 	  TIM_OC_InitTypeDef sConfigOC = {0};
	  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};
      if(dmaFlag == 0){
    	  htim->Instance = arrayTim[indexTim];
    	  	  htim->Init.Prescaler = prescaler;
    	  	  htim->Init.CounterMode = TIM_COUNTERMODE_UP;
    	  	  htim->Init.Period = period;
    	  	  htim->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    	  	  htim->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    	  	  if (HAL_TIM_Base_Init(htim) != HAL_OK)
    	  	  {
    	  	    Error_Handler();
    	  	  }
    	  	  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    	  	  if (HAL_TIM_ConfigClockSource(htim, &sClockSourceConfig) != HAL_OK)
    	  	  {
    	  	    Error_Handler();
    	  	  }
    	  	  if (HAL_TIM_PWM_Init(htim) != HAL_OK)
    	  	  {
    	  	    Error_Handler();
    	  	  }
    	  	  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    	  	  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    	  	  if (HAL_TIMEx_MasterConfigSynchronization(htim, &sMasterConfig) != HAL_OK)
    	  	  {
    	  	    Error_Handler();
    	  	  }
    	  	  sConfigOC.OCMode = TIM_OCMODE_PWM1;
    	  	  sConfigOC.Pulse = 0;
    	  	  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    	  	  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
      }
      else{
    	    pwmDMA();
    	    htim->Instance = TIM1;
    	    htim->Init.Prescaler = 0;
    	    htim->Init.CounterMode = TIM_COUNTERMODE_UP;
    	    htim->Init.Period = 90-1;
    	    htim->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    	    htim->Init.RepetitionCounter = 0;
    	    htim->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    	    if (HAL_TIM_PWM_Init(htim) != HAL_OK)
    	    {
    	      Error_Handler();
    	    }
    	    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    	    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    	    if (HAL_TIMEx_MasterConfigSynchronization(htim, &sMasterConfig) != HAL_OK)
    	    {
    	      Error_Handler();
    	    }
    	    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    	    sConfigOC.Pulse = 0;
    	    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    	    sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
    	    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    	    sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
    	    sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
      }

 	  //TIM1
 	  if(arrayTim[indexTim] == TIM1){
 		  if (HAL_TIM_PWM_ConfigChannel(htim, &sConfigOC, arrayChannel[indexChannel]) != HAL_OK)
 		 	  {
 		 	    Error_Handler();
 		 	  }
 	 	  __HAL_RCC_GPIOA_CLK_ENABLE();
 	 	  switch (indexChannel) {
			case 0:
				if(gpioPWMFlag1 == 0){
					GPIO_PWM_InitStruct[0].Pin = GPIO_PIN_8;
				}
				else{
					GPIO_PWM_InitStruct[0].Pin |= GPIO_PIN_8;
				}
				   gpioPWMFlag1++;
				   if(dmaFlag == 0){
					   HAL_TIM_PWM_Start(htim, TIM_CHANNEL_1);
				   }
				   else{
					   HAL_TIM_PWM_Start_IT(htim, TIM_CHANNEL_1);
				   }
				break;
			case 1:
				if(gpioPWMFlag1 == 0){
					GPIO_PWM_InitStruct[0].Pin = GPIO_PIN_9;
				}
				else{
					GPIO_PWM_InitStruct[0].Pin |= GPIO_PIN_9;
				}
					gpioPWMFlag1++;
				   if(dmaFlag == 0){
					   HAL_TIM_PWM_Start(htim, TIM_CHANNEL_2);
				   }
				   else{
					   HAL_TIM_PWM_Start_IT(htim, TIM_CHANNEL_2);
				   }
				break;
			case 2:
				if(gpioPWMFlag1 == 0){
					GPIO_PWM_InitStruct[0].Pin = GPIO_PIN_10;
				}
				else{
					GPIO_PWM_InitStruct[0].Pin |= GPIO_PIN_10;
				}
					gpioPWMFlag1++;
				   if(dmaFlag == 0){
					   HAL_TIM_PWM_Start(htim, TIM_CHANNEL_3);
				   }
				   else{
					   HAL_TIM_PWM_Start_IT(htim, TIM_CHANNEL_3);
				   }
				break;
			case 3:
				if(gpioPWMFlag1 == 0){
					GPIO_PWM_InitStruct[0].Pin = GPIO_PIN_11;
				}
				else{
					GPIO_PWM_InitStruct[0].Pin |= GPIO_PIN_11;
				}
					gpioPWMFlag1++;
					   if(dmaFlag == 0){
						   HAL_TIM_PWM_Start(htim, TIM_CHANNEL_4);
					   }
					   else{
						  HAL_TIM_PWM_Start_IT(htim, TIM_CHANNEL_4);
					   }
				break;
			default:
				break;
		}
	 	 	if(dmaFlag == 1){
	 	 	  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
	 	 	  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
	 	 	  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
	 	 	  sBreakDeadTimeConfig.DeadTime = 0;
	 	 	  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
	 	 	  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
	 	 	  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
	 	 	  if (HAL_TIMEx_ConfigBreakDeadTime(htim, &sBreakDeadTimeConfig) != HAL_OK)
	 	 	  {
	 	 	    Error_Handler();
	 	 	  }
// 	 	 	    pwmDMA();
	 	 	}
 	 	 	GPIO_PWM_InitStruct[0].Mode = GPIO_MODE_AF_PP;
 	 	 	GPIO_PWM_InitStruct[0].Speed = GPIO_SPEED_FREQ_LOW;
 	 	 	HAL_GPIO_Init(GPIOA, &GPIO_PWM_InitStruct[0]);
 	  		HAL_TIM_Base_Start_IT(htim);
 	  }
 	  //TIM2
 	  else if(arrayTim[indexTim] == TIM2){
 		  if (HAL_TIM_PWM_ConfigChannel(htim, &sConfigOC, arrayChannel[indexChannel]) != HAL_OK)
 		 	  {
 		 	    Error_Handler();
 		 	  }
 	 	  __HAL_RCC_GPIOA_CLK_ENABLE();
 	 	  __HAL_RCC_GPIOB_CLK_ENABLE();
 		  switch (indexChannel) {
			case 0:
				if(gpioPWMFlag2A == 0){
					GPIO_PWM_InitStruct[0].Pin = GPIO_PIN_15;
				}
				else{
					GPIO_PWM_InitStruct[0].Pin |= GPIO_PIN_15;
				}
		 	 	GPIO_PWM_InitStruct[1].Mode = GPIO_MODE_AF_PP;
		 	 	GPIO_PWM_InitStruct[1].Speed = GPIO_SPEED_FREQ_LOW;
		 	 	HAL_GPIO_Init(GPIOA, &GPIO_PWM_InitStruct[1]);
				gpioPWMFlag2A++;
				  HAL_TIM_PWM_Start(htim, TIM_CHANNEL_1);
				break;
			case 1:
				if(gpioPWMFlag2A == 0){
					GPIO_PWM_InitStruct[0].Pin = GPIO_PIN_1;
				}
				else{
					GPIO_PWM_InitStruct[0].Pin |= GPIO_PIN_1;
				}
				gpioPWMFlag2A++;
		 	 	GPIO_PWM_InitStruct[1].Mode = GPIO_MODE_AF_PP;
		 	 	GPIO_PWM_InitStruct[1].Speed = GPIO_SPEED_FREQ_LOW;
		 	 	HAL_GPIO_Init(GPIOA, &GPIO_PWM_InitStruct[1]);
				HAL_TIM_PWM_Start(htim, TIM_CHANNEL_2);
				break;
			case 2:
				if(gpioPWMFlag2B == 0){
					GPIO_PWM_InitStruct[0].Pin = GPIO_PIN_10;
				}
				else{
					GPIO_PWM_InitStruct[0].Pin |= GPIO_PIN_10;
				}
				gpioPWMFlag2B++;
		 	 	GPIO_PWM_InitStruct[1].Mode = GPIO_MODE_AF_PP;
		 	 	GPIO_PWM_InitStruct[1].Speed = GPIO_SPEED_FREQ_LOW;
		 	 	HAL_GPIO_Init(GPIOB, &GPIO_PWM_InitStruct[1]);
				  HAL_TIM_PWM_Start(htim, TIM_CHANNEL_3);
				break;
			case 3:
				if(gpioPWMFlag2B == 0){
					GPIO_PWM_InitStruct[0].Pin = GPIO_PIN_11;
				}
				else{
					GPIO_PWM_InitStruct[0].Pin = GPIO_PIN_11;
				}
				  gpioPWMFlag2B++;
			 	 	GPIO_PWM_InitStruct[1].Mode = GPIO_MODE_AF_PP;
			 	 	GPIO_PWM_InitStruct[1].Speed = GPIO_SPEED_FREQ_LOW;
			 	 	HAL_GPIO_Init(GPIOB, &GPIO_PWM_InitStruct[1]);
				  HAL_TIM_PWM_Start(htim, TIM_CHANNEL_4);
				break;
			default:
				break;
		}
 		    __HAL_AFIO_REMAP_TIM2_ENABLE();
	  		HAL_TIM_Base_Start_IT(htim);
 	  }
 	  //TIM3
 	  else if(arrayTim[indexTim] == TIM3){
 		  if (HAL_TIM_PWM_ConfigChannel(htim, &sConfigOC, arrayChannel[indexChannel]) != HAL_OK)
 		 	  {
 		 	    Error_Handler();
 		 	  }
 	 	  __HAL_RCC_GPIOC_CLK_ENABLE();
 	 	  switch (indexChannel) {
			case 0: //CH1 GPIO
				if(gpioPWMFlag3 == 0){
					GPIO_PWM_InitStruct[2].Pin = GPIO_PIN_6;
				}
				else{
					GPIO_PWM_InitStruct[2].Pin |= GPIO_PIN_6;
				}
				gpioPWMFlag3++;
				   HAL_TIM_PWM_Start(htim, TIM_CHANNEL_1);
				break;
			case 1://CH2
				if(gpioPWMFlag3 == 0){
					GPIO_PWM_InitStruct[2].Pin = GPIO_PIN_7;
				}
				else{
					GPIO_PWM_InitStruct[2].Pin |= GPIO_PIN_7;
				}
					gpioPWMFlag3++;
				  HAL_TIM_PWM_Start(htim, TIM_CHANNEL_2);
				break;
			case 2:
				if(gpioPWMFlag3 == 0){
					GPIO_PWM_InitStruct[2].Pin = GPIO_PIN_8;
				}
				else{
					GPIO_PWM_InitStruct[2].Pin |= GPIO_PIN_8;
				}
					gpioPWMFlag3++;
				  HAL_TIM_PWM_Start(htim, TIM_CHANNEL_3);
				break;
			case 3:
				if(gpioPWMFlag3 == 0){
					GPIO_PWM_InitStruct[2].Pin = GPIO_PIN_9;
				}
				else{
					GPIO_PWM_InitStruct[2].Pin |= GPIO_PIN_9;
				}
				  gpioPWMFlag3++;
				  HAL_TIM_PWM_Start(htim, TIM_CHANNEL_4);
				break;
			default:
				break;
		}
 	 	GPIO_PWM_InitStruct[2].Mode = GPIO_MODE_AF_PP;
 	 	GPIO_PWM_InitStruct[2].Speed = GPIO_SPEED_FREQ_LOW;
 	 	HAL_GPIO_Init(GPIOC, &GPIO_PWM_InitStruct[2]);
 	 	__HAL_AFIO_REMAP_TIM3_ENABLE();

  		  HAL_TIM_Base_Start_IT(htim);
  		HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "GPIO_PWM=%04X\r\n", GPIO_PWM_InitStruct[2].Pin), 1000);
 	  }
 	  //TIM4
 	  else{
 		  if (HAL_TIM_PWM_ConfigChannel(htim, &sConfigOC, arrayChannel[indexChannel]) != HAL_OK)
 		 	  {
 		 	    Error_Handler();
 		 	  }
 	 	  __HAL_RCC_GPIOB_CLK_ENABLE();
 	 	  switch (indexChannel) {
			case 0:
				if(gpioPWMFlag4 == 0){
					GPIO_PWM_InitStruct[3].Pin = GPIO_PIN_6;
				}
				else{
					GPIO_PWM_InitStruct[3].Pin |= GPIO_PIN_6;
				}
				   gpioPWMFlag4++;
				   HAL_TIM_PWM_Start(htim, TIM_CHANNEL_1);
				break;
			case 1:
				if(gpioPWMFlag4 == 0){
					GPIO_PWM_InitStruct[3].Pin = GPIO_PIN_7;
				}
				else{
					GPIO_PWM_InitStruct[3].Pin |= GPIO_PIN_7;
				}
				   gpioPWMFlag4++;
				   HAL_TIM_PWM_Start(htim, TIM_CHANNEL_2);
				break;
			case 2:
				if(gpioPWMFlag4 == 0){
						GPIO_PWM_InitStruct[3].Pin = GPIO_PIN_8;
					}
				else{
						GPIO_PWM_InitStruct[3].Pin |= GPIO_PIN_8;
					}
				   gpioPWMFlag4++;
				   HAL_TIM_PWM_Start(htim, TIM_CHANNEL_3);
				break;
			case 3:
				if(gpioPWMFlag4 == 0){
						GPIO_PWM_InitStruct[3].Pin = GPIO_PIN_9;
					}
				else{
						GPIO_PWM_InitStruct[3].Pin |= GPIO_PIN_9;
					}
				   gpioPWMFlag4++;
				   HAL_TIM_PWM_Start(htim, TIM_CHANNEL_4);
				break;
			default:
				break;
		}
 	 	 	GPIO_PWM_InitStruct[3].Mode = GPIO_MODE_AF_PP;
 	 	 	GPIO_PWM_InitStruct[3].Speed = GPIO_SPEED_FREQ_LOW;
 	 	 	HAL_GPIO_Init(GPIOB, &GPIO_PWM_InitStruct[3]);
 	  		HAL_TIM_Base_Start_IT(htim);
 	  		HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "GPIO_PWM=%04X\r\n", GPIO_PWM_InitStruct[3].Pin), 1000);
 	  }
}
void ADC_MspInit(ADC_HandleTypeDef* hadc)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(hadc->Instance==ADC1)
  {
    /* ADC1 clock enable */
    __HAL_RCC_ADC1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**ADC1 GPIO Configuration
    PA0-WKUP     ------> ADC1_IN0
    PA1     ------> ADC1_IN1
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN ADC1_MspInit 1 */

  /* USER CODE END ADC1_MspInit 1 */
  }
}
void ADC_Config(ADC_HandleTypeDef *hadc, uint8_t index){
	 /* USER CODE BEGIN ADC1_Init 0 */

	  /* USER CODE END ADC1_Init 0 */

	  ADC_ChannelConfTypeDef sConfig = {0};

	  /* USER CODE BEGIN ADC1_Init 1 */

	  /* USER CODE END ADC1_Init 1 */

	  /** Common config
	  */
	  hadc->Instance = ADC1;
	  hadc->Init.ScanConvMode = ADC_SCAN_DISABLE;
	  hadc->Init.ContinuousConvMode = ENABLE;
	  hadc->Init.DiscontinuousConvMode = DISABLE;
	  hadc->Init.ExternalTrigConv = ADC_SOFTWARE_START;
	  hadc->Init.DataAlign = ADC_DATAALIGN_RIGHT;
	  hadc->Init.NbrOfConversion = 1;
	  if (HAL_ADC_Init(hadc) != HAL_OK)
	  {
	    Error_Handler();
	  }

	  /** Configure Regular Channel
	  */
	  sConfig.Channel = ADC_CHANNEL_0;
	  sConfig.Rank = ADC_REGULAR_RANK_1;
	  sConfig.SamplingTime = adcSamplingTime[index];
	  if (HAL_ADC_ConfigChannel(hadc, &sConfig) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  ADC_MspInit(hadc);
	  HAL_ADC_Start(hadc);
}

