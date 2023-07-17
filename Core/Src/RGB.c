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

extern UART_HandleTypeDef huart2;
extern TIM_HandleTypeDef htim1;
extern I2C_HandleTypeDef hi2c1;

uint8_t LED_Data[MAX_LED][4];
uint8_t LED_Mod[MAX_LED][4];

void Set_LED (int LEDnum, int Red, int Green, int Blue){
	LED_Data[LEDnum][0] = LEDnum;
	LED_Data[LEDnum][1] = Green;
	LED_Data[LEDnum][2] = Red;
	LED_Data[LEDnum][3] = Blue;
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
//					HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "!Send1=%d#\r\n", i), 1000);
					pwmData[indx] = 60;  // 2/3 of 90
				}

				else {
//					HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "!Send2=%d#\r\n", i), 1000);
					pwmData[indx] = 30;  // 1/3 of 90
				}

				indx++;
			}

		}

		for (int i=0; i<50; i++)
		{
//			HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "!Indx=%d#\r\n", indx), 1000);
			pwmData[indx] = 0;
			indx++;
		}
		HAL_Delay(100);
//		HAL_UART_Transmit(&huart2, (uint8_t*)"Before HAL_TIM_PWM_Start_DMA()\r\n", strlen("Before HAL_TIM_PWM_Start_DMA()\r\n"), 100);
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
		HAL_StatusTypeDef status = HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)pwmData, 10);
		HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "status=%02X#\r\n", status), 1000);
//		HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "status=%02X#\r\n", status), 1000);
		if(status == HAL_OK){
			HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "status=%02X#\r\n", status), 1000);
		}
//		HAL_UART_Transmit(&huart2, (uint8_t*)"After HAL_TIM_PWM_Start_DMA()\r\n", strlen("After HAL_TIM_PWM_Start_DMA()\r\n"), HAL_MAX_DELAY);
//		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 70);
//		HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "!pwmData[30]=%d#\r\n", pwmData[30]), 1000);
		while (!datasentflag){};
		datasentflag = 0;
//		HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "status=%02X#\r\n", status), 1000);
}

void testBuzzer(void){
	for(uint8_t i = 0; i< 100; ++i){
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, i);
	}
}

