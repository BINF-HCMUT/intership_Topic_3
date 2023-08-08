/*
 * global.h
 *
 *  Created on: Jun 21, 2023
 *      Author: Acer
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
// parameter for DHT20_FSM
#define INIT	0

#define READING_STATE	11
#define FAN_ON			12
#define FAN_OFF			13
extern uint8_t DHT20_status;


#define MAX_BUFFER_SIZE 30
#define MAX_LED 4
#define USE_BRIGHTNESS 1
#define PI 3.14159265
#define Tim	4
#define CHANNEL 4
#define NUM_OF_SAMPLINGTIME 8

#define PWM_DMA_STREAM  DMA1_Channel2

// Define the PWM timer and channel you want to use
#define PWM_TIMER       TIM1
#define PWM_CHANNEL     TIM_CHANNEL_2

//define status for fsmNeopixelRgbLed
#define neopixelInit		0
#define neopixelSingleLed 	1
#define neopixelAllLed		2
#define neopixelCycleLed 	3

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
//adc config
extern uint32_t adcSamplingTime[NUM_OF_SAMPLINGTIME];

//fsm led RGB
extern int neopixelStatus;

#endif /* INC_GLOBAL_H_ */
