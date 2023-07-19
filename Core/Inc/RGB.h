/*
 * RGB.h
 *
 *  Created on: Jul 5, 2023
 *      Author: Acer
 */

#ifndef INC_RGB_H_
#define INC_RGB_H_

#include "stdint.h"


void Set_LED (int LEDnum, int Red, int Green, int Blue);
void Set_Brightness (int brightness);
void WS2812_Send (void);
void testBuzzer(void);
uint8_t rainbow_effect_left();
uint8_t rainbow_effect_right();

#endif /* INC_RGB_H_ */
