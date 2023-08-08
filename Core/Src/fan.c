/*
 * fan.c
 *
 *  Created on: Aug 8, 2023
 *      Author: Acer
 */
#include"fan.h"

void setFan(uint8_t dutyCycle){
    // Giới hạn giá trị duty cycle từ 0 đến 100
    if (dutyCycle > 100) {
        dutyCycle = 100;
    }

    __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, dutyCycle);
}

void resetFan(void){
	__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,0);
}
