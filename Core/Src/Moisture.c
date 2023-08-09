/*
 * Moisture.c
 *
 *  Created on: Jul 28, 2023
 *      Author: Acer
 */


#include "Moisture.h"
#include "global.h"
#include "main.h"
#include "config.h"
#include "stdio.h"

#define MAX_ADC_VALUE 4095
extern UART_HandleTypeDef huart2;
extern ADC_HandleTypeDef hadc1;

uint8_t high = 0;
uint8_t low = 1;

void Relay(){
	      if(ADC_Moisture_Value >= 20){
	    	  ledStatus(GPIOA, 10, high);
	      }
	      else{
	    	  ledStatus(GPIOA, 10, low);
	      }
}

void Moisture_readValue(){
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 1000);
	ADC_Moisture_Value =  HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1);
	Moisture_convert();
	HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "!ADC_Value=%lu\r\n", ADC_Moisture_Value), 1000);
}

void Moisture_convert(){
	ADC_Moisture_Value =  (ADC_Moisture_Value*100/MAX_ADC_VALUE);
}
