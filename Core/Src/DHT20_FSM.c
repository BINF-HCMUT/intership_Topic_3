/*
 * DHT20_FSM.c
 *
 *  Created on: Aug 3, 2023
 *      Author: admin
 */

#include "DHT20_FSM.h"

void DHT20_FSM(void){
	switch (status) {
		case INIT:
			status = READING_STATE;
			break;
		case READING_STATE:
			setTimer1(10000);
			DHT20_Read();
			LCD_Display_Temp(DHT20_getTemp());
			LCD_Display_Humid(DHT20_getHumid());
			if (DHT20_getTemp() > 29.3)	status = FAN_ON;
			else status = FAN_OFF;
			break;
		case FAN_ON:
			setFan(50);
			if(timer1_flag == 1)	status = READING_STATE;
			break;
		case FAN_OFF:
			resetFan();
			if(timer1_flag == 1)	status =READING_STATE;
			break;
		default:
			break;
	}
}
