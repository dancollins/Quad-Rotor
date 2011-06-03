/*
	Quad Rotor Flight Controller
	file: motor.h
	author: Dan Collins
	date: June 03
*/
#ifndef MOTOR_H
#define MOTOR_H

void motor_init(void);
void motor_refresh(PWMDriver*);
void motor_set(uint16_t thrust);

#endif
