/*
 * global.h
 *
 *  Created on: Jul 28, 2023
 *      Author: admin
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "software_timer.h"
#include "i2c-lcd.h"
#include "fan.h"
#include "DHT.h"
#define MAX_LED 4

#define INIT	0

#define READING_STATE	11
#define FAN_ON			12
#define FAN_OFF			13


int status;

//define status for fsmNeopixelRgbLed
#define neopixelInit		0
#define neopixelSingleLed 	1
#define neopixelAllLed		2
#define neopixelCycleLed 	3

extern int neopixelStatus;
extern int NeoPixel_status;

extern uint32_t NeoPixel_RGB_Color;

#endif /* INC_GLOBAL_H_ */
