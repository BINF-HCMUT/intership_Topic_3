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
