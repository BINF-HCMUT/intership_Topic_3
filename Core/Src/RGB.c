/*
 * RGB.c
 *
 *  Created on: Jul 5, 2023
 *      Author: Acer
 */

#include "RGB.h"
#include <stdint.h>
#include "global.h"
#include "math.h"
#include "stm32f1xx_hal.h"

extern UART_HandleTypeDef huart2;
extern TIM_HandleTypeDef htim1;
extern I2C_HandleTypeDef hi2c1;
extern DMA_HandleTypeDef hdma_tim1_ch1;

uint8_t LED_Data[MAX_LED][4];
uint8_t LED_Mod[MAX_LED][4];

void Set_LED (int LEDnum, int Red, int Green, int Blue){
	LED_Data[LEDnum][0] = LEDnum;
	LED_Data[LEDnum][1] = Green;
	LED_Data[LEDnum][2] = Red;
	LED_Data[LEDnum][3] = Blue;

//	HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "LED_Data[0]=%d\r\n", LED_Data[LEDnum][0]), 1000);
//	HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "LED_Data[1]=%d\r\n", LED_Data[LEDnum][1]), 1000);
//	HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "LED_Data[2]=%d\r\n", LED_Data[LEDnum][2]), 1000);
//	HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "LED_Data[3]=%d\r\n", LED_Data[LEDnum][3]), 1000);
}

void Set_Brightness (int brightness){
#if USE_BRIGHTNESS

	if (brightness > 45) brightness = 45;
	for (int i=0; i<MAX_LED; i++)
	{
		LED_Mod[i][0] = LED_Data[i][0];
		for (int j=1; j<4; j++)
		{
			float angle = 90-brightness;  // in degrees
			angle = angle*PI / 180;  // in rad
			LED_Mod[i][j] = (LED_Data[i][j])/(tan(angle));
		}
	}

#endif
}


void WS2812_Send (void){
	uint32_t indx=0;
	uint32_t color;

		for (int i= 0; i<MAX_LED; i++)
		{
	#if USE_BRIGHTNESS
			color = ((LED_Mod[i][1]<<16) | (LED_Mod[i][2]<<8) | (LED_Mod[i][3]));
	#else
			color = ((LED_Data[i][1]<<16) | (LED_Data[i][2]<<8) | (LED_Data[i][3]));

	#endif

			for (int i=23; i>=0; i--)
			{
				if (color&(1<<i))
				{
					pwmData[indx] = 60;  // 2/3 of 90
				}

				else {
					pwmData[indx] = 30;  // 1/3 of 90
				}

				indx++;
			}

		}

		for (int i=0; i<50; i++)
		{
			pwmData[indx] = 0;
			indx++;
		}
		HAL_Delay(100);
		HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "indx=%d\r\n", indx), 1000);

		HAL_DMA_StateTypeDef timState;
		timState = HAL_TIM_PWM_GetState(&htim1);
		HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "timState=%02X\r\n", timState), 1000);
		if (HAL_TIM_PWM_GetState(&htim1) != HAL_TIM_STATE_READY)
		{
		  HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1); // Dừng TIM nếu nó đang hoạt động
		}
		HAL_Delay(10);
		timState = HAL_TIM_PWM_GetState(&htim1);
		HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "timState=%02X\r\n", timState), 1000);
//		 if (status == HAL_OK)
//		    {
//			   __HAL_TIM_ENABLE_IT(&htim1, TIM_IT_UPDATE);
//			   HAL_Delay(10);
//				HAL_StatusTypeDef newStatus = HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)pwmData, 10);
//				HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "newstatus=%02X#\r\n", newStatus), 1000);
//				if(newStatus == HAL_OK){
//					HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "status=%02X#\r\n", newStatus), 1000);
//				}
//		    }
		HAL_DMA_StateTypeDef dmaState;
		dmaState = HAL_DMA_GetState(&hdma_tim1_ch1);
		HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "dmaState=%02X\r\n", dmaState), 1000);
		if (dmaState == HAL_DMA_STATE_BUSY || dmaState ==  HAL_DMA_STATE_TIMEOUT )
		{
			HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "dmaState=%02X\r\n", dmaState), 1000);
		}
		else{
							HAL_StatusTypeDef newStatus = HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)pwmData, indx);
							HAL_Delay(100);
							dmaState = HAL_DMA_GetState(&hdma_tim1_ch1);
							if(newStatus == HAL_OK){
								HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "newstatus=%02X#\r\n", newStatus), 1000);
								HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "dmaState=%02X#\r\n", dmaState), 1000);
							}
		}
		HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "dmaState=%02X#\r\n", dmaState), 1000);
				while (!datasentflag){};
				datasentflag = 0;
}

void Reset_LED (void)
{
	for (int i=0; i<MAX_LED; i++)
	{
		LED_Data[i][0] = i;
		LED_Data[i][1] = 0;
		LED_Data[i][2] = 0;
		LED_Data[i][3] = 0;
	}
}


// ported from the arduino code for 8 LEDs located at ->>>>  https://adrianotiger.github.io/Neopixel-Effect-Generator/

uint16_t effStep = 0;

uint8_t rainbow_effect_left() {
  float factor1, factor2;
  uint16_t ind;
  for(uint16_t j=0;j<8;j++) {
    ind = effStep + j * 1.625;
    switch((int)((ind % 13) / 4.333333333333333)) {
      case 0: factor1 = 1.0 - ((float)(ind % 13 - 0 * 4.333333333333333) / 4.333333333333333);
              factor2 = (float)((int)(ind - 0) % 13) / 4.333333333333333;
              Set_LED(j, 255 * factor1 + 0 * factor2, 0 * factor1 + 255 * factor2, 0 * factor1 + 0 * factor2);
              WS2812_Send();
              break;
      case 1: factor1 = 1.0 - ((float)(ind % 13 - 1 * 4.333333333333333) / 4.333333333333333);
              factor2 = (float)((int)(ind - 4.333333333333333) % 13) / 4.333333333333333;
              Set_LED(j, 0 * factor1 + 0 * factor2, 255 * factor1 + 0 * factor2, 0 * factor1 + 255 * factor2);
              WS2812_Send();
              break;
      case 2: factor1 = 1.0 - ((float)(ind % 13 - 2 * 4.333333333333333) / 4.333333333333333);
              factor2 = (float)((int)(ind - 8.666666666666666) % 13) / 4.333333333333333;
              Set_LED(j, 0 * factor1 + 255 * factor2, 0 * factor1 + 0 * factor2, 255 * factor1 + 0 * factor2);
              WS2812_Send();
              break;
    }
  }
  if(effStep >= 13) {effStep=0; return 0x03; }
  else effStep++;
  return 0x01;
}



uint8_t rainbow_effect_right() {
  float factor1, factor2;
  uint16_t ind;
  for(uint16_t j=0;j<8;j++) {
    ind = 14 - (int16_t)(effStep - j * 1.75) % 14;
    switch((int)((ind % 14) / 4.666666666666667)) {
      case 0: factor1 = 1.0 - ((float)(ind % 14 - 0 * 4.666666666666667) / 4.666666666666667);
              factor2 = (float)((int)(ind - 0) % 14) / 4.666666666666667;
              Set_LED(j, 255 * factor1 + 0 * factor2, 0 * factor1 + 255 * factor2, 0 * factor1 + 0 * factor2);
              WS2812_Send();
              break;
      case 1: factor1 = 1.0 - ((float)(ind % 14 - 1 * 4.666666666666667) / 4.666666666666667);
              factor2 = (float)((int)(ind - 4.666666666666667) % 14) / 4.666666666666667;
              Set_LED(j, 0 * factor1 + 0 * factor2, 255 * factor1 + 0 * factor2, 0 * factor1 + 255 * factor2);
              WS2812_Send();
              break;
      case 2: factor1 = 1.0 - ((float)(ind % 14 - 2 * 4.666666666666667) / 4.666666666666667);
              factor2 = (float)((int)(ind - 9.333333333333334) % 14) / 4.666666666666667;
              Set_LED(j, 0 * factor1 + 255 * factor2, 0 * factor1 + 0 * factor2, 255 * factor1 + 0 * factor2);
              WS2812_Send();
              break;
    }
  }
  if(effStep >= 14) {effStep = 0; return 0x03; }
  else effStep++;
  return 0x01;
}

void testBuzzer(void){
//	for(uint8_t i = 0; i< 100; ++i){
//		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, i);
//	}
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 100);
}

