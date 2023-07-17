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
uint8_t datasentflag = 1;
uint8_t backlight_state = 1;
