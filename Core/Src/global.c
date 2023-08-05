/*
 * global.c
 *
 *  Created on: Jun 21, 2023
 *      Author: Acer
 */


#include "global.h"

uint8_t temp = 0;
uint8_t index_buffer = 0;
uint8_t buffer_flag = 0;
uint8_t str[12] = "GOATMESSI";
uint16_t pwmData[(24*MAX_LED)+50] = {0};
uint8_t datasentflag;uint8_t datasentflag = 1;
uint8_t backlight_state = 1;
uint32_t NeoPixel_RGB_Color = 0xE7BC;
uint16_t GPIO_PIN[16] = {
		0x0001,
		0x0002,
		0x0004,
		0x0008,
		0x0010,
		0x0020,
		0x0040,
		0x0080,
		0x0100,
		0x0200,
		0x0400,
		0x0800,
		0x1000,
		0x2000,
		0x4000,
		0x8000
};
uint8_t NeoPixel_status = 0;
uint32_t ADC_Moisture_Value = 0;

TIM_TypeDef* arrayTim[Tim] = {TIM1, TIM2, TIM3, TIM4};
uint32_t arrayChannel[CHANNEL] = { TIM_CHANNEL_1,  TIM_CHANNEL_2,  TIM_CHANNEL_3,  TIM_CHANNEL_4};
uint8_t gpioPWMFlag1 = 0;
uint8_t gpioPWMFlag2A = 0;
uint8_t gpioPWMFlag2B = 0;
uint8_t gpioPWMFlag3 = 0;
uint8_t gpioPWMFlag4 = 0;
GPIO_InitTypeDef GPIO_PWM_InitStruct[4] = {0};

//ADC_Config
uint32_t adcSamplingTime[NUM_OF_SAMPLINGTIME] = {
		0x00000000,
		0x00000001,
		0x00000002,
		0x00000003,
		0x00000004,
		0x00000005,
		0x00000006,
		0x00000007,
};

//fsm led rgb
int neopixelStatus = 0;
