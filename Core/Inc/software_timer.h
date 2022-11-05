/*
 * software_timer.h
 *
 *  Created on: Nov 5, 2022
 *      Author: pmt12
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_
#define TIMER_CYCLE 10
extern int timer0_flag;
extern int timer1_flag;
extern int timer2_flag;
extern int timer3_flag;

extern int timer0_counter;
extern int timer1_counter;
extern int timer2_counter;
extern int timer3_counter;


void setTimer0(int duration);
void setTimer1(int duration);
void setTimer2(int duration);
void setTimer3(int duration);

void timer_run();

#endif /* INC_SOFTWARE_TIMER_H_ */
