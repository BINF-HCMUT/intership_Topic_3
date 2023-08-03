/*
 * Moisture.c
 *
 *  Created on: Jul 28, 2023
 *      Author: Acer
 */


#include "Moisture.h"
#include "global.h"
#include "main.h"

#define MAX_ADC_VALUE 4095
extern UART_HandleTypeDef huart2;
extern ADC_HandleTypeDef hadc1;
void Moisture_readValue(){
	ADC_Moisture_Value =  HAL_ADC_GetValue(&hadc1);
	Moisture_convert();
	HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "!ADC_Value=%lu\r\n", ADC_Moisture_Value), 1000);
	HAL_Delay(3000);
}
void Moisture_convert(){
	ADC_Moisture_Value =  (ADC_Moisture_Value*100/MAX_ADC_VALUE);
}
