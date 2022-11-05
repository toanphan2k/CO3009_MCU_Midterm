/*
 * button.c
 *
 *  Created on: Nov 5, 2022
 *      Author: pmt12
 */

#include "button.h"
#include "main.h"
#include "software_timer.h"

static GPIO_PinState buttonBuffer[NUM_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer1[NUM_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2[NUM_OF_BUTTONS];
static uint8_t flagForLongPress3s[NUM_OF_BUTTONS];
static uint16_t counterLongPress3s[NUM_OF_BUTTONS];

void getKeyInput() {
	for ( int i = 0; i < NUM_OF_BUTTONS ; i ++) {
		debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
		if(i == RESET_INDEX){
			debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(BTN_RESET_GPIO_Port, BTN_RESET_Pin);
		}
		if(i == INC_INDEX){
			debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(BTN_INC_GPIO_Port,BTN_INC_Pin);
		}
		if(i == DEC_INDEX){
			debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(BTN_DEC_GPIO_Port,BTN_DEC_Pin);
		}
		if( debounceButtonBuffer1[i] == debounceButtonBuffer2[i])
			buttonBuffer[i] = debounceButtonBuffer1[i];
		if( buttonBuffer[i] == BTN_PRESSED) {
			if( counterLongPress3s[i] < LONG_PRESSED_DURATION/TIMER_CYCLE) {
				counterLongPress3s[i]++;
			} else {
				flagForLongPress3s[i] = 1;
			}

		} else {
			counterLongPress3s[i] = 0;
			flagForLongPress3s[i] = 0;
		}
	}
}
unsigned char is_button_pressed (uint8_t index) {
	if(index >= NUM_OF_BUTTONS) return 0;
	return (buttonBuffer[index] == BTN_PRESSED );
}
unsigned char is_button_pressed_3s(unsigned char index) {
	if(index >= NUM_OF_BUTTONS) return 0xff ;
	return (flagForLongPress3s[index] == 1) ;
}


