#include "i2c-LCD.h"
#include "stdio.h"


//Define global variable for backlight state
uint8_t backlight_state = 1;

void LCD_scanI2CAddresses() {
	char str[20] = {0};
    for (uint8_t address = 0; address < 128; address++) {
        if (HAL_I2C_IsDeviceReady(&hi2c1, address, 1, 10) == HAL_OK) {
        	//HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "!address=%02X#\r\n", address), 100);
        }
    }
}

void LCD_isConnected(){
	HAL_StatusTypeDef status = HAL_I2C_IsDeviceReady(&hi2c1, I2C_ADDR, 1, 100);
	if(status == HAL_OK){
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 1);
	}
}

void LCD_Set_Backlight(uint8_t state) {
  if (state) {
    backlight_state = 1;
  } else {
    backlight_state = 0;
  }
}

void LCD_Send_CMD (char cmd){
	uint8_t EN1 = 0x04|(backlight_state << BL_BIT);
	uint8_t EN0 = 0x00|(backlight_state << BL_BIT);

	uint8_t buffer[4] = {
			(cmd & 0xF0)|EN1,	//en=1, rs=0
			(cmd & 0xF0)|EN0,	//en=0, rs=0
			(cmd << 4)|EN1,		//en=1, rs=0
			(cmd << 4)|EN0	 	//en=0, rs=0
	};
	HAL_I2C_Master_Transmit (&hi2c1, I2C_ADDR,buffer, 4, 100);
}

void LCD_Send_Data (char data){

	uint8_t EN1 = 0x05|(backlight_state << BL_BIT);
	uint8_t EN0 = 0x01|(backlight_state << BL_BIT);

	uint8_t buffer[4] = {
			(data & 0xF0)|EN1,	//en=1, rs=1
			(data & 0xF0)|EN0,	//en=0, rs=1
			(data << 4)|EN1,	//en=1, rs=1
			(data << 4)|EN0		//en=0, rs=1
	};
	HAL_I2C_Master_Transmit (&hi2c1, I2C_ADDR,buffer, 4, 100);
}

void LCD_Clear (void){
	LCD_Send_CMD (0x01);
	HAL_Delay(2);
}

void LCD_Set_Cursor(uint8_t row, uint8_t col){
    switch (row)
    {
        case 0:
            col |= 0x80;
            break;
        case 1:
            col |= 0xC0;
            break;
    }
    LCD_Send_CMD (col);
}


void LCD_init (void){
	// 4 bit initialisation
	HAL_Delay(50);  // wait for >40ms
	LCD_Send_CMD (0x30);
	HAL_Delay(5);  // wait for >4.1ms
	LCD_Send_CMD (0x30);
	HAL_Delay(1);  // wait for >100us
	LCD_Send_CMD (0x30);
	HAL_Delay(10);
	LCD_Send_CMD (0x20);  // 4bit mode
	HAL_Delay(10);

  // dislay initialisation
	LCD_Send_CMD (0x28);
	HAL_Delay(1);
	LCD_Send_CMD (0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
	HAL_Delay(1);
	LCD_Send_CMD(0x01);		 //Clear display
	HAL_Delay(1);
	HAL_Delay(1);
	LCD_Send_CMD(0x06);		 //Auto Increment cursor
	HAL_Delay(1);
	LCD_Send_CMD(0x0C);		 //Display ON Cursor OFF
	HAL_Delay(1);

	LCD_Set_Backlight(1);
}

void LCD_Send_String (char *str){
	while (*str) LCD_Send_Data (*str++);
}

void LCD_Send_Number (int number){
	char buffer[8];
	sprintf(buffer,"%d",number);
	LCD_Send_String(buffer);
}

void LCD_Display_Temp(float Temp){
	char str[20] = {0};
	sprintf(str, "TEMP: %.2f", Temp);
	LCD_Set_Cursor(0,0);
	LCD_Send_String(str);
	LCD_Send_Data('C');
}

void LCD_Display_Humid(float Humid){
	char str[20] = {0};
	sprintf(str, "HUMID: %.2f", Humid);
	LCD_Set_Cursor(1,0);
	LCD_Send_String(str);
	LCD_Send_Data('%');
}
