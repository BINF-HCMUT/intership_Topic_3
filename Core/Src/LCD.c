/*
 * LCD.c
 *
 *  Created on: Jun 28, 2023
 *      Author: Acer
 */
#include "LCD.h"
#include "stdio.h"
#include "global.h"
extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart2;

uint8_t displayMode;
uint8_t backlightVal;
uint8_t displayFunction;
uint8_t displayControl;

void lcdBegin(){
	displayFunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;

	displayControl = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;

	backlightVal = LCD_BACKLIGHT;
	expanderWrite(backlightVal);
    HAL_Delay(1000);

	// Initialize to default text direction (for roman languages)
	displayMode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
	// set the entry mode
	lcdSendCmd(LCD_ENTRYMODESET | displayMode);
}

void isLcdConnected(){
	HAL_StatusTypeDef status = HAL_I2C_IsDeviceReady(&hi2c1, SLAVE_ADDRESS_LCD, 1, 100);
	HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "!Connect=%02X#\r\n", status), 100);
}

void lcdSendCmd (char cmd)
{
    char data_u, data_l;
	uint8_t data_t[4];
	data_u = (cmd&0xf0);
	data_l = ((cmd<<4)&0xf0);
	data_t[0] = data_u|0x0C;  //en=1, rs=0
	data_t[1] = data_u|0x08;  //en=0, rs=0
	data_t[2] = data_l|0x0C;  //en=1, rs=0
	data_t[3] = data_l|0x08;  //en=0, rs=0
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

void scanI2CAddresses() {
    for (uint8_t address = 0; address < 128; address++) {
        if (HAL_I2C_IsDeviceReady(&hi2c1, address, 1, 10) == HAL_OK) {
        	HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "!address=%02X#\r\n", address), 100);
        }
    }
}
void lcdSendData(char data)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u|0x0D;  //en=1, rs=0
	data_t[1] = data_u|0x09;  //en=0, rs=0
	data_t[2] = data_l|0x0D;  //en=1, rs=0
	data_t[3] = data_l|0x09;  //en=0, rs=0
	HAL_I2C_Master_Transmit(&hi2c1, SLAVE_ADDRESS_LCD, data_t, 4, 1000);
}

void lcdClear (void)
{
	lcdSendCmd(LCD_CLEARDISPLAY);
	HAL_Delay(2);
}

void lcdSetCursor(int row, int col)
{
    switch (row)
    {
        case 0:
            col |= 0x80;
            break;
        case 1:
            col |= 0xC0;
            break;
    }

    lcdSendCmd (col);
}

void lcdNoCursor(){
	displayControl &= ~LCD_CURSORON;
	lcdSendCmd(LCD_DISPLAYCONTROL | displayControl);
}

void lcdCursor(){
	displayControl |= LCD_CURSORON;
	lcdSendCmd(LCD_DISPLAYCONTROL | displayControl);
}

void lcdHome(void){
	lcdSendCmd(LCD_RETURNHOME); // set cursor position to zero
	HAL_Delay(2);
}

void lcdNoBlink(){
	displayControl &= ~LCD_BLINKON;
	lcdSendCmd(LCD_DISPLAYCONTROL | displayControl);
}

void lcdBlink(){
	displayControl |= LCD_BLINKON;
	lcdSendCmd(LCD_DISPLAYCONTROL | displayControl);
}

void lcdInit (void)
{
	// 4 bit initialisation
	HAL_Delay(50);  // wait for >40ms
	lcdSendCmd (0x30);
	HAL_Delay(5);  // wait for >4.1ms
	lcdSendCmd (0x30);
	HAL_Delay(1);  // wait for >100us
	lcdSendCmd (0x30);
	HAL_Delay(10);
	lcdSendCmd (0x20);  // 4bit mode
	HAL_Delay(10);

  // dislay initialisation
	lcdSendCmd (0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	HAL_Delay(1);
	lcdSendCmd (0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
	HAL_Delay(1);
	lcdSendCmd (0x01);  // clear display
	HAL_Delay(1);
	lcdSendCmd (0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	HAL_Delay(1);
	lcdSendCmd (0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
}

void lcdSendString (char *str)
{
	while (*str) lcdSendData (*str++);
}

void lcdSendNumber(float number)
{
	char buffer[8];
	sprintf(buffer,"%f",number);
	lcdSendString(buffer);
}

void lcdLeftToRight(void){
	displayMode |= LCD_ENTRYLEFT;
	lcdSendCmd(LCD_ENTRYMODESET | displayMode);
}

void lcdRightToLeft(){
	displayMode &= ~LCD_ENTRYLEFT;
	lcdSendCmd(LCD_ENTRYMODESET | displayMode);
}

void expanderWrite(uint8_t data){
	data |= backlightVal;
	HAL_I2C_Master_Transmit(&hi2c1, SLAVE_ADDRESS_LCD, &data, 1, 100);
}

void lcdNoBacklight(){
	backlightVal = LCD_NOBACKLIGHT;
	expanderWrite(0);
}

void lcdBacklight(){
	backlightVal = LCD_BACKLIGHT;
	expanderWrite(0);
}

void lcdSetBacklight(uint8_t state){
	if(state){
		lcdBacklight();
	}
	else{
		lcdNoBacklight();
	}
}

void lcdScrollDisplayLeft(){
	lcdSendCmd(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

void scdScrollDisplayRight(){
	lcdSendCmd(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

void lcdAutoScroll(){
	displayMode |= LCD_ENTRYSHIFTINCREMENT;
	lcdSendCmd(LCD_ENTRYMODESET | displayMode);
}

void lcdNoAutosSroll(){
	displayMode &= ~LCD_ENTRYSHIFTINCREMENT;
	lcdSendCmd(LCD_ENTRYMODESET | displayMode);
}


