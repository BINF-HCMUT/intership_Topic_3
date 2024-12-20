/*
 * newRGB.c
 *
 *  Created on: Jul 19, 2023
 *      Author: Acer
 */

#include "newRGB.h"
#include "global.h"
#include "math.h"
#include "stm32f1xx_hal.h"
#include "main.h"

extern TIM_HandleTypeDef htim1;
extern DMA_HandleTypeDef hdma_tim1_ch2;

#define PWM_HI (57)
#define PWM_LO (29)

// LED parameters
 #define NUM_BPP (3) // WS2812B
//#define NUM_BPP (4) // SK6812
#define NUM_PIXELS (8)
#define NUM_BYTES (NUM_BPP * NUM_PIXELS)

// LED color buffer
uint8_t rgb_arr[NUM_BYTES] = {0};

// LED write buffer
#define WR_BUF_LEN (NUM_BPP * 8 * 2)
uint8_t wr_buf[WR_BUF_LEN] = {0};
uint_fast8_t wr_buf_p = 0;

uint8_t r;
uint8_t g;
uint8_t b;

uint8_t angle = 0;
const uint8_t angle_difference = 11;

static inline uint8_t scale8(uint8_t x, uint8_t scale) {
  return ((uint16_t)x * scale) >> 8;
}

void NeoPixel_clear_all_led(){
	   for (uint_fast8_t i = 0; i < NUM_PIXELS; ++i) {
	#if (NUM_BPP == 4) // SK6812
	        rgb_arr[4 * i] = 0;          // G = 0
	        rgb_arr[4 * i + 1] = 0;      // R = 0
	        rgb_arr[4 * i + 2] = 0;      // B = 0
	        rgb_arr[4 * i + 3] = 0;      // Reserved = 0
	#else // WS2812B
	        rgb_arr[3 * i] = 0;          // G = 0
	        rgb_arr[3 * i + 1] = 0;      // R = 0
	        rgb_arr[3 * i + 2] = 0;      // B = 0
	#endif // End SK6812 WS2812B case differentiation
	    }
	    NeoPixel_led_render(); // Ghi dữ liệu mới vào LED
		HAL_Delay(200);
}

void NeoPixel_toggleLed(){
	if(NeoPixel_status == 0){
		 NeoPixel_clear_all_led();
	}
	else{
		 NeoPixel_hslColor(120, 255, 127);
		 NeoPixel_led_set_all_RGB();
	}
	NeoPixel_status =  !NeoPixel_status;
}
// Set a single color (RGB) to index
void NeoPixel_led_set_RGB(uint8_t index) {
	r = (NeoPixel_RGB_Color >> 16) & 0xFF;
	g = (NeoPixel_RGB_Color >> 8) & 0xFF;
	b =  NeoPixel_RGB_Color & 0xFF;
#if (NUM_BPP == 4) // SK6812
  rgb_arr[4 * index] = scale8(g, 0xB0); // g;
  rgb_arr[4 * index + 1] = r;
  rgb_arr[4 * index + 2] = scale8(b, 0xF0); // b;
  rgb_arr[4 * index + 3] = 0;
#else // WS2812B
  rgb_arr[3 * index] = scale8(g, 0xB0); // g;
  rgb_arr[3 * index + 1] = r;
  rgb_arr[3 * index + 2] = scale8(b, 0xF0); // b;
#endif // End SK6812 WS2812B case differentiation
}

// Set all colors to RGB
void NeoPixel_led_set_all_RGB() {
  for(uint_fast8_t i = 0; i < NUM_PIXELS; ++i) {
	  NeoPixel_led_set_RGB(i);
  }
	NeoPixel_led_render();
}

// Shuttle the data to the LEDs!
void NeoPixel_led_render() {
  if(wr_buf_p != 0 || hdma_tim1_ch2.State != HAL_DMA_STATE_READY) {
    // Ongoing transfer, cancel!
    for(uint8_t i = 0; i < WR_BUF_LEN; ++i) wr_buf[i] = 0;
    wr_buf_p = 0;
    HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_1);
    return;
  }
  // Ooh boi the first data buffer half (and the second!)
#if (NUM_BPP == 4) // SK6812
  for(uint_fast8_t i = 0; i < 8; ++i) {
    wr_buf[i     ] = PWM_LO << (((rgb_arr[0] << i) & 0x80) > 0);
    wr_buf[i +  8] = PWM_LO << (((rgb_arr[1] << i) & 0x80) > 0);
    wr_buf[i + 16] = PWM_LO << (((rgb_arr[2] << i) & 0x80) > 0);
    wr_buf[i + 24] = PWM_LO << (((rgb_arr[3] << i) & 0x80) > 0);
    wr_buf[i + 32] = PWM_LO << (((rgb_arr[4] << i) & 0x80) > 0);
    wr_buf[i + 40] = PWM_LO << (((rgb_arr[5] << i) & 0x80) > 0);
    wr_buf[i + 48] = PWM_LO << (((rgb_arr[6] << i) & 0x80) > 0);
    wr_buf[i + 56] = PWM_LO << (((rgb_arr[7] << i) & 0x80) > 0);
  }
#else // WS2812B
  for(uint_fast8_t i = 0; i < 8; ++i) {
    wr_buf[i     ] = PWM_LO << (((rgb_arr[0] << i) & 0x80) > 0);
    wr_buf[i +  8] = PWM_LO << (((rgb_arr[1] << i) & 0x80) > 0);
    wr_buf[i + 16] = PWM_LO << (((rgb_arr[2] << i) & 0x80) > 0);
    wr_buf[i + 24] = PWM_LO << (((rgb_arr[3] << i) & 0x80) > 0);
    wr_buf[i + 32] = PWM_LO << (((rgb_arr[4] << i) & 0x80) > 0);
    wr_buf[i + 40] = PWM_LO << (((rgb_arr[5] << i) & 0x80) > 0);
  }
#endif // End SK6812 WS2812B case differentiation
//	HAL_StatusTypeDef newStatus = HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)wr_buf, WR_BUF_LEN);
//	HAL_Delay(100);
//	HAL_DMA_StateTypeDef dmaState;
//	dmaState = HAL_DMA_GetState(&hdma_tim1_ch2);
//	if(newStatus == HAL_OK){
//		HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "newstatus=%02X#\r\n", newStatus), 1000);
//		HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "dmaState=%02X#\r\n", dmaState), 1000);
//	}
  HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)wr_buf, WR_BUF_LEN);
  wr_buf_p = 2; // Since we're ready for the next buffer
}

void HAL_TIM_PWM_PulseFinishedHalfCpltCallback(TIM_HandleTypeDef *htim) {
  // DMA buffer set from LED(wr_buf_p) to LED(wr_buf_p + 1)
  if(wr_buf_p < NUM_PIXELS) {
    // We're in. Fill the even buffer
#if (NUM_BPP == 4) // SK6812
    for(uint_fast8_t i = 0; i < 8; ++i) {
      wr_buf[i     ] = PWM_LO << (((rgb_arr[4 * wr_buf_p    ] << i) & 0x80) > 0);
      wr_buf[i +  8] = PWM_LO << (((rgb_arr[4 * wr_buf_p + 1] << i) & 0x80) > 0);
      wr_buf[i + 16] = PWM_LO << (((rgb_arr[4 * wr_buf_p + 2] << i) & 0x80) > 0);
      wr_buf[i + 24] = PWM_LO << (((rgb_arr[4 * wr_buf_p + 3] << i) & 0x80) > 0);
    }
#else // WS2812B
    for(uint_fast8_t i = 0; i < 8; ++i) {
      wr_buf[i     ] = PWM_LO << (((rgb_arr[3 * wr_buf_p    ] << i) & 0x80) > 0);
      wr_buf[i +  8] = PWM_LO << (((rgb_arr[3 * wr_buf_p + 1] << i) & 0x80) > 0);
      wr_buf[i + 16] = PWM_LO << (((rgb_arr[3 * wr_buf_p + 2] << i) & 0x80) > 0);
    }
#endif // End SK6812 WS2812B case differentiation
    wr_buf_p++;
  } else if (wr_buf_p < NUM_PIXELS + 2) {
    // Last two transfers are resets. SK6812: 64 * 1.25 us = 80 us == good enough reset
  	//                               WS2812B: 48 * 1.25 us = 60 us == good enough reset
    // First half reset zero fill
    for(uint8_t i = 0; i < WR_BUF_LEN / 2; ++i) wr_buf[i] = 0;
    wr_buf_p++;
  }
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim) {
  // DMA buffer set from LED(wr_buf_p) to LED(wr_buf_p + 1)
  if(wr_buf_p < NUM_PIXELS) {
    // We're in. Fill the odd buffer
#if (NUM_BPP == 4) // SK6812
    for(uint_fast8_t i = 0; i < 8; ++i) {
      wr_buf[i + 32] = PWM_LO << (((rgb_arr[4 * wr_buf_p    ] << i) & 0x80) > 0);
      wr_buf[i + 40] = PWM_LO << (((rgb_arr[4 * wr_buf_p + 1] << i) & 0x80) > 0);
      wr_buf[i + 48] = PWM_LO << (((rgb_arr[4 * wr_buf_p + 2] << i) & 0x80) > 0);
      wr_buf[i + 56] = PWM_LO << (((rgb_arr[4 * wr_buf_p + 3] << i) & 0x80) > 0);
    }
#else // WS2812B
    for(uint_fast8_t i = 0; i < 8; ++i) {
      wr_buf[i + 24] = PWM_LO << (((rgb_arr[3 * wr_buf_p    ] << i) & 0x80) > 0);
      wr_buf[i + 32] = PWM_LO << (((rgb_arr[3 * wr_buf_p + 1] << i) & 0x80) > 0);
      wr_buf[i + 40] = PWM_LO << (((rgb_arr[3 * wr_buf_p + 2] << i) & 0x80) > 0);
    }
#endif // End SK6812 WS2812B case differentiation
    wr_buf_p++;
  } else if (wr_buf_p < NUM_PIXELS + 2) {
    // Second half reset zero fill
    for(uint8_t i = WR_BUF_LEN / 2; i < WR_BUF_LEN; ++i) wr_buf[i] = 0;
    ++wr_buf_p;
  } else {
    // We're done. Lean back and until next time!
    wr_buf_p = 0;
    HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_1);
  }
}

void NeoPixel_set_led_cycle(){
	for(uint8_t i = 0; i < MAX_LED; i++) {
		 NeoPixel_hslColor(angle + (i * angle_difference), 255, 127);
		 NeoPixel_led_set_RGB(i);
	}
	++angle;
	NeoPixel_led_render();
	HAL_Delay(10);
}

void  NeoPixel_hslColor(uint8_t h, uint8_t s, uint8_t l){
	NeoPixel_hsl_to_rgb(h, s, l);
}
void NeoPixel_hsl_to_rgb(uint8_t h, uint8_t s, uint8_t l) {
	if(l == 0) return;

	volatile uint8_t  r, g, b, lo, c, x, m;
	volatile uint16_t h1, l1, H;
	l1 = l + 1;
	if (l < 128)    c = ((l1 << 1) * s) >> 8;
	else            c = (512 - (l1 << 1)) * s >> 8;

	H = h * 6;              // 0 to 1535 (actually 1530)
	lo = H & 255;           // Low byte  = primary/secondary color mix
	h1 = lo + 1;

	if ((H & 256) == 0)   x = h1 * c >> 8;          // even sextant, like red to yellow
	else                  x = (256 - h1) * c >> 8;  // odd sextant, like yellow to green

	 m = l - (c >> 1);
	 switch(H >> 8) {       // High byte = sextant of colorwheel
	 case 0 : r = c; g = x; b = 0; break; // R to Y
	 case 1 : r = x; g = c; b = 0; break; // Y to G
	 case 2 : r = 0; g = c; b = x; break; // G to C
	 case 3 : r = 0; g = x; b = c; break; // C to B
	 case 4 : r = x; g = 0; b = c; break; // B to M
	 default: r = c; g = 0; b = x; break; // M to R
	}
     NeoPixel_RGB_Color = (((uint32_t)r + m) << 16) | (((uint32_t)g + m) << 8) | ((uint32_t)b + m);
}
