/*
 * fsm_control.h
 *
 *  Created on: Nov 5, 2022
 *      Author: pmt12
 */

#ifndef INC_FSM_CONTROL_H_
#define INC_FSM_CONTROL_H_

enum ButtonState{ IDLE, RESET_PRESSED, RESET_LONGPRESSED
				, INC_PRESSED, INC_LONGPRESSED, DEC_PRESSED, DEC_LONGPRESSED};
extern enum ButtonState btnState;

enum LedState{ON, OFF};
extern enum LedState ledState;
void fsm_simple_button_run();
void ledAuto();

#endif /* INC_FSM_CONTROL_H_ */
