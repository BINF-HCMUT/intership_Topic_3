/*
 * DHT.c
 *
 *  Created on: Jul 18, 2023
 *      Author: admin
 */
#include"DHT.h"
#define DHT20_ADDRESS 0x38 << 1
extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart2;

char str[50] = {0};
float humidity          = 0;
float temperature       = 0;
uint8_t checksum;
uint8_t buf[7] = {0};
uint8_t readCMD[3] = {0xAC, 0x33, 0x00};

float DHT20_getTemp(void){
	return temperature;
}

float DHT20_getHumid(void){
	return humidity;
}

void scanI2CAddresses() {
    for (uint8_t address = 0; address < 128; address++) {
        if (HAL_I2C_IsDeviceReady(&hi2c1, address, 1, 10) == HAL_OK) {
        	HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "!address=%02X#\r\n", address), 100);
        }
    }
}

uint8_t DHT20_isConnected(){
	HAL_StatusTypeDef status = HAL_I2C_IsDeviceReady(&hi2c1, DHT20_ADDRESS, 1, 100);
	HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "!connectDHT=%02X#\r\n", status), 1000);
    return status;
}

uint8_t DHT20_requestData(){
	  HAL_StatusTypeDef ret;
	  ret =  HAL_I2C_Master_Transmit(&hi2c1, DHT20_ADDRESS, readCMD, 3, 1000);
      return ret;
}

uint8_t DHT20_crc8(uint8_t *ptr, uint8_t len)
{
	uint8_t crc = 0xFF;
	while(len--){
		crc ^= *ptr++;
		for(uint8_t i = 0; i< 8; ++i)
		{
			if(crc & 0x80)
			{
				crc <<= 1;
				crc ^= 0x31;
			}
			else
			{
				crc <<= 1;
			}
		}
	}
	return crc;
}

int DHT20_Read(){
	HAL_StatusTypeDef ret ;
	if(DHT20_isConnected() != HAL_OK){
		return DHT20_ERROR_CONNECT;
	}
    uint8_t request_data = DHT20_requestData();
    if(request_data == HAL_OK){
    	HAL_Delay(1000);
    	HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "!result=%s#\r\n", "OK"), 1000);
    	ret = HAL_I2C_Master_Receive(&hi2c1, DHT20_ADDRESS, buf, 7, 100);
    	HAL_Delay(100);
    	   if(ret == HAL_OK){
    		   return DHT20_Convert();
    	   }

    }
    return DHT20_ERROR_BYTES_ALL_ZERO;
}

int DHT20_Convert(){
	   //  convert temperature

	   uint32_t raw = buf[1];
	   raw <<= 8;
	   raw += buf[2];
	   raw <<= 4;
	   raw += (buf[3] >> 4);
	   humidity = raw * 9.5367431640625e-5;   // ==> / 1048576.0 * 100%;
	   HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "Humid=%f\r\n", humidity), 1000);

		//  convert humidity
	    raw = (buf[3] & 0x0F);
	    raw <<= 8;
	    raw += buf[4];
	    raw <<= 8;
	    raw += buf[5];
	    temperature = raw * 1.9073486328125e-4 - 50;  //  ==> / 1048576.0 * 200 - 50;
	    HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "Temp=%f\r\n", temperature), 1000);

	    // Checksum
	    uint8_t crc = DHT20_crc8(buf, 6);
	    if(crc != buf[6]){
	    	return DHT20_ERROR_CHECKSUM;
	    }
	    HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "!CRC=%s#\r\n", "OK"), 1000);
	    return DHT20_OK;
}
