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
void motor_set(int16_t thrust, int16_t pitch, int16_t roll, int16_t yaw);

#endif
