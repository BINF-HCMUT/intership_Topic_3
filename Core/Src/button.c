/*
 * button.c
 *
 *  Created on: Jun 21, 2023
 *      Author: Acer
 */


#include "button.h"

//we aim to work with more than one buttons
#define N0_OF_BUTTONS 				       3
//timer interrupt duration is 10ms, so to pass 3 second,
//we need to jump to the interrupt service routine 100 time
#define DURATION_FOR_AUTO_INCREASING	300
// when button is pressed more than 3s, it 'll turn on flag each 1s to update value counterLED
#define DURATION_FOR_MORE_THAN_3s 100
#define BUTTON_IS_PRESSED   GPIO_PIN_RESET
#define BUTTON_IS_RELEASED   GPIO_PIN_SET
#define BUTTON_PRESSED_MORE_THAN_3s	2

#define BUTTON_PRESSED GPIO_PIN_RESET // 0
#define BUTTON_RELEASED GPIO_PIN_SET  // 1
//the buffer that the final result is stored after
//debouncing
static GPIO_PinState buttonBuffer[N0_OF_BUTTONS];
//we define two buffers for debouncing
static GPIO_PinState debounceButtonBuffer1[N0_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2[N0_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer3[N0_OF_BUTTONS];
//we define a flag for a button pressed more than 1 second.
static uint8_t flagForButtonPress3s[N0_OF_BUTTONS];
static uint8_t flag1s[N0_OF_BUTTONS];
//we define counter for automatically increasing the value
//after the button is pressed more than 1 second.
static uint16_t counterForButtonPress3s[N0_OF_BUTTONS];
static int buttonState[N0_OF_BUTTONS] = {BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED};
static int button_flag[N0_OF_BUTTONS];
void getKeyProcess(int index){// turn on button_flag
	if(index >= 0 && index < N0_OF_BUTTONS){
		button_flag[index] = 1;
	}
}
// this function turn on flagForButtonPress3s when button is pressed more than 3s
void get3sFlag(int index){
	if(index >= 0 && index < N0_OF_BUTTONS){
			flagForButtonPress3s[index] = 1;
		}
}
void clear3sFlag(int index){
	if(index >= 0 && index < N0_OF_BUTTONS){
			flagForButtonPress3s[index] = 0;
		}
}
void get1sFlag(int index){
	if(index >= 0 && index < N0_OF_BUTTONS){
				flag1s[index] = 1;
			}
}
void fsm_input_processing(GPIO_PinState buttonBuffer[], int index){
	switch(buttonState[index]){
	case BUTTON_IS_PRESSED:
		//if button is pressed more than 3s
		if(counterForButtonPress3s[index] < DURATION_FOR_AUTO_INCREASING){
			counterForButtonPress3s[index]++;
			if(counterForButtonPress3s[index] == DURATION_FOR_AUTO_INCREASING){
				buttonState[index] = BUTTON_PRESSED_MORE_THAN_3s;
				counterForButtonPress3s[index] = 0;
				getKeyProcess(index);
				get3sFlag(index);
			}
		}
		// button is release
		if(buttonBuffer[index] == BUTTON_RELEASED){
			buttonState[index] = BUTTON_IS_RELEASED;
			counterForButtonPress3s[index] = 0;

		}
		break;
	case BUTTON_IS_RELEASED:
		//button is pressed
		if(buttonBuffer[index] == BUTTON_PRESSED){
			buttonState[index] = BUTTON_IS_PRESSED;
			getKeyProcess(index);
		}
		break;
	case BUTTON_PRESSED_MORE_THAN_3s:
		if(counterForButtonPress3s[index] < DURATION_FOR_MORE_THAN_3s ){
					counterForButtonPress3s[index]++;
					if(counterForButtonPress3s[index] == DURATION_FOR_MORE_THAN_3s){
						buttonState[index] = BUTTON_PRESSED_MORE_THAN_3s;
						counterForButtonPress3s[index] = 0;
						get1sFlag(index);
						getKeyProcess(index);
						get3sFlag(index);

					}
				}
		if(buttonBuffer[index] == BUTTON_RELEASED){
			buttonState[index] = BUTTON_IS_RELEASED;
			counterForButtonPress3s[index] = 0;
			//set up 3 flags = 0
			flagForButtonPress3s[index] = 0;
			flag1s[index] = 0;
			button_flag[index] = 0;
		}
		break;
	default:
		break;
	}
}
void button_reading(void){
	for(uint8_t i = 0; i < N0_OF_BUTTONS; i++){
		debounceButtonBuffer3[i] = debounceButtonBuffer2[i];
		debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
		// Chosing Which button is pressed.
		switch(i){
		case 0: // read signal from button0
			debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(Button0_GPIO_Port, Button0_Pin);
			break;
		case 1://  read signal from button0
			debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(Button1_GPIO_Port, Button1_Pin);
			break;
		case 2://  read signal from button0
			debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(Button2_GPIO_Port, Button2_Pin);
			break;
		default:
			break;
		}
		if((debounceButtonBuffer3[i] == debounceButtonBuffer2[i]) && (debounceButtonBuffer2[i] == debounceButtonBuffer1[i])){
			buttonBuffer[i] = debounceButtonBuffer3[i];
			fsm_input_processing(buttonBuffer,i);
		}

	}
}
int is_button_pressed(uint8_t index){
	if(index >= N0_OF_BUTTONS) return 0;
	if(button_flag[index] == 1){
		//set button flag value = 0
		button_flag[index] = 0;
		return 1;
	}
	return 0;
}
int is_long_pressed(uint8_t index){
	if(index >= N0_OF_BUTTONS) return 0;
	if(flagForButtonPress3s[index] == 1){
		return 1;
	}
	return 0;
}
// using to check each 1s then update value counterLed
int is_1s(uint8_t index){
	if(index >= N0_OF_BUTTONS) return 0;
		if(flag1s[index] == 1){
			flag1s[index] = 0;
			return 1;
		}
		return 0;
}
