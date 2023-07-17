/*
 * button.h
 *
 *  Created on: Jun 21, 2023
 *      Author: Acer
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"
#include "global.h"

void button_reading(void);

int is_button_pressed(uint8_t index);
int is_long_pressed(uint8_t index);
int is_1s(uint8_t index);


#endif /* INC_BUTTON_H_ */
