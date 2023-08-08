#include "stm32f1xx_hal.h"
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
