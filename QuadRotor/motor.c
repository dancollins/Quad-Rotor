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
	1000000,
	1000000 / 50,
	0
};

uint16_t motors[4];

void motor_init(void) {
	pwmStart(&PWMD2, &pwmcfg);
	
	palSetPadMode(GPIOA, 0, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
	palSetPadMode(GPIOA, 1, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
	palSetPadMode(GPIOA, 2, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
	palSetPadMode(GPIOA, 3, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
	
	pwmEnableChannel(&PWMD2, 0, 1000);
	pwmEnableChannel(&PWMD2, 1, 1000);
	pwmEnableChannel(&PWMD2, 2, 1000);
	pwmEnableChannel(&PWMD2, 3, 1000);
}

void motor_refresh(PWMDriver *pwmp) {
	(void)pwmp;
	pwmEnableChannel(&PWMD2, 0, 1000 + motors[0]);
	pwmEnableChannel(&PWMD2, 1, 1000 + motors[1]);
	pwmEnableChannel(&PWMD2, 2, 1000 + motors[2]);
	pwmEnableChannel(&PWMD2, 3, 1000 + motors[3]);
}

void motor_set(uint16_t thrust) {
	motors[0] = thrust;
}
