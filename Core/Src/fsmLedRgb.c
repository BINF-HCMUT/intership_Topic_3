/*
 * fsmLedRgb.c
 *
 *  Created on: Aug 4, 2023
 *      Author: Acer
 */

#include "fsmLedRgb.h"
uint8_t index = 0;

void fsmNeopixelRgbLed(){
	switch (neopixelStatus) {
		case neopixelInit:
			NeoPixel_hslColor(120, 255, 127);
			if(is_button_pressed(0) == 1){
				    NeoPixel_hslColor(120, 255, 127);
				    NeoPixel_led_set_RGB(0);
				    NeoPixel_led_render();
			}
			if(is_button_pressed(1) == 1){
				NeoPixel_clear_all_led();
				 NeoPixel_hslColor(120, 255, 127);
				NeoPixel_led_set_RGB(index++);
			    NeoPixel_led_render();
			    neopixelStatus = neopixelSingleLed;
			}
			break;
		case neopixelSingleLed:
			if(is_button_pressed(0) == 1){
				if(index >=4) index = 0;
				NeoPixel_clear_all_led();
				NeoPixel_hslColor(120, 255, 127);
				NeoPixel_led_set_RGB(index++);
			    NeoPixel_led_render();
			}
			if(is_button_pressed(1) == 1){
				index = 0;
				NeoPixel_clear_all_led();
				NeoPixel_hslColor(120, 255, 127);
				NeoPixel_toggleLed();
				neopixelStatus = neopixelAllLed;
			}
			break;
		case neopixelAllLed:
			if(is_button_pressed(2) == 1){
				NeoPixel_toggleLed();
			}
			if(is_button_pressed(1) == 1){
				NeoPixel_clear_all_led();
				HAL_Delay(100);
				NeoPixel_set_led_cycle();
				neopixelStatus = neopixelCycleLed;
			}
			break;
		case neopixelCycleLed:
			NeoPixel_set_led_cycle();
			if(is_button_pressed(1) == 1){
				NeoPixel_clear_all_led();
				neopixelStatus = neopixelInit;
			}
			break;
		default:
			break;
	}
}
