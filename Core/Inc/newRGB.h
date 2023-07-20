/*
 * newRGB.h
 *
 *  Created on: Jul 19, 2023
 *      Author: Acer
 */

#ifndef INC_NEWRGB_H_
#define INC_NEWRGB_H_

#include "glob.h"
#include <stdint.h>

void led_set_RGB(uint8_t index, uint8_t r, uint8_t g, uint8_t b);
void led_set_RGBW(uint8_t index, uint8_t r, uint8_t g, uint8_t b, uint8_t w);
void led_set_all_RGB(uint8_t r, uint8_t g, uint8_t b);
void led_set_all_RGBW(uint8_t r, uint8_t g, uint8_t b, uint8_t w);
void led_render();


#endif /* INC_NEWRGB_H_ */
