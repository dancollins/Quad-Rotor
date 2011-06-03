/*
	Quad Rotor Flight Controller
	file: motor.c
	author: Dan Collins
	date: June 03
*/
#include <ch.h>
#include <hal.h>

#include "motor.h"

static PWMConfig pwmcfg = {
	motor_refresh,
	{
		{PWM_OUTPUT_ACTIVE_HIGH, NULL},
		{PWM_OUTPUT_ACTIVE_HIGH, NULL},
		{PWM_OUTPUT_ACTIVE_HIGH, NULL},
		{PWM_OUTPUT_ACTIVE_HIGH, NULL}
	},
	SYS,
	PWM_COMPUTE_ARR(10000, 1000000),
	0
};

uint16_t motors[4];

void motor_init(void) {
	pwmStart(&PWMD2, &pwmcfg);
	
	pwmEnableChannel(&PWMD2, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD2, 5000));
	pwmEnableChannel(&PWMD2, 1, 1000);
	pwmEnableChannel(&PWMD2, 2, 1000);
	pwmEnableChannel(&PWMD2, 3, 1000);
}

void motor_refresh(PWMDriver *pwmp) {
	(void)pwmp;
	pwmEnableChannel(&PWMD2, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD2, 5000));
	pwmEnableChannel(&PWMD2, 1, 1000 + motors[1]);
	pwmEnableChannel(&PWMD2, 2, 1000 + motors[2]);
	pwmEnableChannel(&PWMD2, 3, 1000 + motors[3]);
}

void motor_set(uint16_t thrust) {
	motors[0] = thrust;
}
