/*
 * DHT20_FSM.c
 *
 *  Created on: Aug 8, 2023
 *      Author: Acer
 */
#include "DHT20_FSM.h"

void DHT20_FSM(void){
	switch (DHT20_status) {
		case INIT:
			DHT20_status = READING_STATE;
			break;
		case READING_STATE:
			setTimer1(5000);
			int result = DHT20_Read();
			LCD_Clear();
			LCD_Display_Temp(DHT20_getTemp());
			LCD_Display_Humid(DHT20_getHumid());
			if (DHT20_getTemp() > 26.3)	DHT20_status = FAN_ON;
			else DHT20_status = FAN_OFF;
			break;
		case FAN_ON:
			setFan(100);
			if(timer1_flag == 1)	DHT20_status = READING_STATE;
			break;
		case FAN_OFF:
			resetFan();
			if(timer1_flag == 1)	DHT20_status =READING_STATE;
			break;
		default:
			break;
	}
}
