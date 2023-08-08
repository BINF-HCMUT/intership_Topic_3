/*

 * LCD.h
 *
 *  Created on: Jun 28, 2023
 *      Author: Acer


#ifndef INC_LCD_H_
#define INC_LCD_H_

#define SLAVE_ADDRESS_LCD 0x21 << 1
// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04#include "stm32f1xx_hal.h"
#include "i2c.h"
#include "math.h"

extern I2C_HandleTypeDef hi2c1;
#define I2C_ADDR 0x21 << 1
#define BL_BIT 3 // Backlight bit

void LCD_scanI2CAddresses();

void LCD_init (void);   // initialize LCD

void LCD_Send_CMD (char cmd);  // send command to the LCD

void LCD_Send_Data (char data);  // send data to the LCD

void LCD_Send_String (char *str);  // send string to the LCD

void LCD_Set_Cursor(uint8_t row, uint8_t col);  // put cursor at the entered position row (0 or 1), col (0-15);

void LCD_Clear (void);

void LCD_Set_Backlight(uint8_t state);

void LCD_Send_Number (int number);

void LCD_isConnected();

void LCD_Display_Temp(float Temp);

void LCD_Display_Humid(float Humid);
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

// flags for backlight control
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00

#define En B00000100  // Enable bit
#define Rw B00000010  // Read/Write bit
#define Rs B00000001  // Register select bit

//Constrast
#define LCD_COMMAND_SET_CONTRAST 0x39
#define LCD_COMMAND_SET_CONTRAST_VALUE 0x70

#include "stm32f1xx_hal.h"

void lcdBegin();
void lcdDisplay();
void lcdNoDisplay();
void lcdNoBlink();
void lcdBlink();
void lcdNoCursor();
void lcdCursor();
void lcdNoBacklight();
void lcdBacklight();
void lcdInit (void);   // initialize lcd
void lcdHome(void);
void lcdSendCmd (char cmd);  // send command to the lcd
void lcdSendData (char data);  // send data to the lcd
void lcdSendString (char *str);  // send string to the lcd
void lcdSetCursor(int row, int col);  // put cursor at the entered position row (0 or 1), col (0-15);
void lcdClear (void);
void isLcdConnected();
void lcdSendNumber(float number);
void lcdLeftToRight(void);
void lcdRightToLeft(void);
void scanI2cAddresses();
void expanderWrite(uint8_t data);
void lcdScrollDisplayLeft();
void lcdScrollDisplayRight();
void lcdAutoScroll();
void lcdNoAutosSroll();

// Compatibility API function aliases
void setBacklight(uint8_t state);


#endif  INC_LCD_H_
*/

#include "stm32f1xx_hal.h"
#include "math.h"

extern I2C_HandleTypeDef hi2c1;
#define I2C_ADDR 0x21 << 1
#define BL_BIT 3 // Backlight bit

void LCD_scanI2CAddresses();

void LCD_init (void);   // initialize LCD

void LCD_Send_CMD (char cmd);  // send command to the LCD

void LCD_Send_Data (char data);  // send data to the LCD

void LCD_Send_String (char *str);  // send string to the LCD

void LCD_Set_Cursor(uint8_t row, uint8_t col);  // put cursor at the entered position row (0 or 1), col (0-15);

void LCD_Clear (void);

void LCD_Set_Backlight(uint8_t state);

void LCD_Send_Number (int number);

void LCD_isConnected();

void LCD_Display_Temp(float Temp);

void LCD_Display_Humid(float Humid);
