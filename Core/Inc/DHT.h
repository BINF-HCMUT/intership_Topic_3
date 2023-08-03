/*
 * DHT.h
 *
 *  Created on: Jul 18, 2023
 *      Author: admin
 */

#ifndef INC_DHT_H_
#define INC_DHT_H_
#include"gpio.h"
#include"main.h"
#include"i2c-lcd.h"



#define DHT20_OK                             0
#define DHT20_ERROR_CHECKSUM                -10
#define DHT20_ERROR_CONNECT                 -11
#define DHT20_MISSING_BYTES                 -12
#define DHT20_ERROR_BYTES_ALL_ZERO          -13
#define DHT20_ERROR_READ_TIMEOUT            -14
#define DHT20_ERROR_LASTREAD                -15

void scanI2CAddresses();
float DHT20_getTemp(void);
float DHT20_getHumid(void);
int DHT20_Read (void);
void isDHTConnected(void);
uint8_t DHT20_isConnected();

#endif /* INC_DHT_H_ */
