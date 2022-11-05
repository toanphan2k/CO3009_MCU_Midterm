/*
 * fsm_control.c
 *
 *  Created on: Nov 5, 2022
 *      Author: pmt12
 */
#include "main.h"
#include "fsm_control.h"
#include "button.h"
#include "software_timer.h"
#include "sevenSegmentLed.h"

int wasInResetPressed = 0;
int wasInINCPressed = 0;
int wasInDECPressed = 0;

int timer0_flag;
int timer1_flag;
int timer2_flag;
int timer3_flag;

int counter = 0;
int ledCounter = 100;

enum ButtonState btnState = IDLE;
enum LedState ledState = ON;

void fsm_simple_button_run(){
	switch(btnState){
	case IDLE:
		if(timer2_flag == 1){
			counter --;
			if(counter <= 0) counter = 0;
			setTimer2(1000);
		}
		if(wasInResetPressed == 1){
			counter = 0;
			wasInResetPressed = 0;
		}
		if(wasInINCPressed == 1){
			counter ++;
			if(counter >= 9) counter = 9;
			wasInINCPressed = 0;
		}

		if(wasInDECPressed == 1){
			counter --;
			if(counter <= 0) counter = 0;
			wasInDECPressed = 0;
		}
		display7Seg(counter);
		if(is_button_pressed(RESET_INDEX)) btnState = RESET_PRESSED;
		if(is_button_pressed(INC_INDEX)) btnState = INC_PRESSED;
		if(is_button_pressed(DEC_INDEX)) btnState = DEC_PRESSED;
		break;
	case RESET_PRESSED:
		if(!is_button_pressed(RESET_INDEX)){
			wasInResetPressed = 1;
			btnState = IDLE;
		}
		break;
	case RESET_LONGPRESSED:
		break;
	case INC_PRESSED:
		if(!is_button_pressed(INC_INDEX)){
			wasInINCPressed = 1;
			btnState = IDLE;
			setTimer2(10000);
		}
		if(is_button_pressed(INC_INDEX)){
			if(is_button_pressed_3s(INC_INDEX)){
				btnState = INC_LONGPRESSED;
				timer0_flag = 1;
			}
		}
		break;
	case INC_LONGPRESSED:
		if(timer0_flag == 1){
			counter++;
			if(counter >= 9) counter = 9;
			setTimer0(1000);
			display7Seg(counter);
		}
		if(!is_button_pressed(INC_INDEX)){
			btnState = IDLE;
			setTimer2(10000);
		}
		break;
	case DEC_PRESSED:

		if(!is_button_pressed(DEC_INDEX)){
			wasInDECPressed = 1;
			btnState = IDLE;
			setTimer2(10000);
		}
		if(is_button_pressed(DEC_INDEX)){
			if(is_button_pressed_3s(DEC_INDEX)){
				btnState = DEC_LONGPRESSED;
				timer1_flag = 1;
			}
		}
		break;
	case DEC_LONGPRESSED:
		if(timer1_flag == 1){
			counter--;
			if(counter <= 0) counter = 0;
			setTimer1(1000);
			display7Seg(counter);
		}
		if(!is_button_pressed(DEC_INDEX)){
			btnState = IDLE;
			setTimer2(10000);
		}
		break;
	}
}

void ledAuto(){
	switch(ledState){
	case ON:
		HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
		if(timer3_flag == 1){
			setTimer3(1000);
			ledState = OFF;
		}
		break;
	case OFF:
		HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
		if(timer3_flag == 1){
			setTimer3(1000);
			ledState = ON;
		}
		break;
	}
}
