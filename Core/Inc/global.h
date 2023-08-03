/*
 * global.h
 *
 *  Created on: Jul 28, 2023
 *      Author: admin
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "software_timer.h"
#include "i2c-lcd.h"
#include "fan.h"
#include "DHT.h"

#define INIT	0

#define READING_STATE	11
#define FAN_ON			12
#define FAN_OFF			13

int status;

#endif /* INC_GLOBAL_H_ */
