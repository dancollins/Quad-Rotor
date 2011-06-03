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
	PWM_COMPUTE_PSC(STM32_TIMCLK1, 1000000), // System Clock(Hz), PWM Clock(Hz)
	PWM_COMPUTE_ARR(1000000, 20000000), // PWM Clock(Hz), Duty Cycle(nS)
	0
};

uint16_t motors[4] = {500, 500, 500, 500};

void motor_init(void) {
	pwmStart(&PWMD2, &pwmcfg);
	
	pwmEnableChannel(&PWMD2, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD2, 500)); // 1mS Pulse
	pwmEnableChannel(&PWMD2, 1, PWM_PERCENTAGE_TO_WIDTH(&PWMD2, 500)); // 1mS Pulse
	pwmEnableChannel(&PWMD2, 2, PWM_PERCENTAGE_TO_WIDTH(&PWMD2, 500)); // 1mS Pulse
	pwmEnableChannel(&PWMD2, 3, PWM_PERCENTAGE_TO_WIDTH(&PWMD2, 500)); // 1mS Pulse
}

void motor_refresh(PWMDriver *pwmp) {
	(void)pwmp;
	pwmEnableChannel(&PWMD2, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD2, motors[0]));
	pwmEnableChannel(&PWMD2, 1, PWM_PERCENTAGE_TO_WIDTH(&PWMD2, motors[1]));
	pwmEnableChannel(&PWMD2, 2, PWM_PERCENTAGE_TO_WIDTH(&PWMD2, motors[2]));
	pwmEnableChannel(&PWMD2, 3, PWM_PERCENTAGE_TO_WIDTH(&PWMD2, motors[3]));
}

void motor_set(uint16_t thrust) {
	motors[0] = thrust;
}
