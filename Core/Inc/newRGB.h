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

void	 NeoPixel_hslColor(uint8_t h, uint8_t s, uint8_t l);
void     NeoPixel_led_set_RGB(uint8_t index);
void     NeoPixel_led_set_all_RGB();
void     NeoPixel_led_render();
void     NeoPixel_hsl_to_rgb(uint8_t h, uint8_t s, uint8_t l);
void	 NeoPixel_set_led_cycle();


#endif /* INC_NEWRGB_H_ */
