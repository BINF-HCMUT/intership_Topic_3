/*
 * global.h
 *
 *  Created on: Jun 21, 2023
 *      Author: Acer
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#define MAX_BUFFER_SIZE 30
#define MAX_LED 4
#define USE_BRIGHTNESS 1
#define PI 3.14159265
#define Tim	4
#define CHANNEL 4

#define PWM_DMA_STREAM  DMA1_Channel2

// Define the PWM timer and channel you want to use
#define PWM_TIMER       TIM1
#define PWM_CHANNEL     TIM_CHANNEL_2

extern uint8_t temp;
extern uint8_t index_buffer;
extern uint8_t buffer_flag;
extern uint8_t str[12];
extern uint16_t pwmData[(24*MAX_LED)+50];
extern uint8_t backlight_state;
extern uint8_t datasentflag;

extern uint32_t NeoPixel_RGB_Color;
extern uint8_t NeoPixel_status;

//gpio config
extern uint16_t GPIO_PIN[16];

//Moisture
extern uint32_t ADC_Moisture_Value;

//pwm config
extern TIM_TypeDef* arrayTim[Tim];
extern uint32_t arrayChannel[CHANNEL];
extern uint8_t gpioPWMFlag1;
extern uint8_t gpioPWMFlag2A;
extern uint8_t gpioPWMFlag2B;
extern uint8_t gpioPWMFlag3;
extern uint8_t gpioPWMFlag4;
extern GPIO_InitTypeDef GPIO_PWM_InitStruct[4];

#endif /* INC_GLOBAL_H_ */
