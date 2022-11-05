/*
 * button.h
 *
 *  Created on: Nov 5, 2022
 *      Author: pmt12
 */
#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_
#include "main.h"

#define NUM_OF_BUTTONS 			3
#define LONG_PRESSED_DURATION 	3000
#define BTN_PRESSED 			GPIO_PIN_RESET
#define BTN_IDLE 				GPIO_PIN_SET
#define RESET_INDEX 			0
#define INC_INDEX 				1
#define DEC_INDEX 				2

void getKeyInput();
unsigned char is_button_pressed(uint8_t index);
unsigned char is_button_pressed_3s(unsigned char index);

#endif /* INC_BUTTON_H_ */
