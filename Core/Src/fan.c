/*
 * fan.c
 *
 *  Created on: Jul 24, 2023
 *      Author: admin
 */
#include"fan.h"

void setFan(uint8_t dutyCycle){
    // Giới hạn giá trị duty cycle từ 0 đến 100
    if (dutyCycle > 100) {
        dutyCycle = 100;
    }

    __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, dutyCycle);
}

void resetFan(void){
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,0);
}
