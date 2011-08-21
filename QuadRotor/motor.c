/*
	Quad Rotor Flight Controller
	file: motor.c
	author: Dan Collins
	date: June 03
*/
#include <ch.h>
#include <hal.h>

#include "motor.h"

#include <math.h>

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

uint16_t motors[4] = {0, 0, 0, 0};

void motor_init(void) {
	pwmStart(&PWMD2, &pwmcfg);
	
	pwmEnableChannel(&PWMD2, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD2, 500)); // 1mS Pulse
	pwmEnableChannel(&PWMD2, 1, PWM_PERCENTAGE_TO_WIDTH(&PWMD2, 500)); // 1mS Pulse
	pwmEnableChannel(&PWMD2, 2, PWM_PERCENTAGE_TO_WIDTH(&PWMD2, 500)); // 1mS Pulse
	pwmEnableChannel(&PWMD2, 3, PWM_PERCENTAGE_TO_WIDTH(&PWMD2, 500)); // 1mS Pulse
}

void motor_refresh(PWMDriver *pwmp) {
	(void)pwmp;
	static uint8_t led_state = 0;
	pwmEnableChannel(&PWMD2, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD2, 500 + motors[0]));
	pwmEnableChannel(&PWMD2, 1, PWM_PERCENTAGE_TO_WIDTH(&PWMD2, 500 + motors[1]));
	pwmEnableChannel(&PWMD2, 2, PWM_PERCENTAGE_TO_WIDTH(&PWMD2, 500 + motors[2]));
	pwmEnableChannel(&PWMD2, 3, PWM_PERCENTAGE_TO_WIDTH(&PWMD2, 500 + motors[3]));
	if (led_state) {
		led_state = 0;
		palSetPad(IOPORT2, GPIOB_LED2); // Turn LED off
	} else {
		led_state = 1;
		palClearPad(IOPORT2, GPIOB_LED2); // Turn LED on
	}
}

void motor_set(int16_t thrust, int16_t pitch, int16_t roll, int16_t yaw) {
	if(thrust < 0) {
		thrust = 0;
	}
	if(thrust > 900) {
		thrust = 900;
	}
	
	// Check that total thrust will not be exceeded.
	if(abs(pitch) + abs(roll) > thrust) {
		// If saturated by pitch/roll, drop yaw component.
		yaw = 0;
		
		// Scale pitch and roll.
		int32_t df = ((abs(pitch) + abs(roll)) << 16) / thrust;
		
		pitch = (pitch << 16) / df;
		roll = (roll << 16) / df;
	
	} else if(abs(pitch) + abs(roll) + abs(yaw) > thrust) {
		// Scale yaw value.
		yaw = (yaw > 0 ? 1 : -1) * (thrust - abs(pitch) - abs(roll));
	}
	
	motors[0] = thrust + pitch + roll - yaw;
	motors[1] = thrust + pitch - roll + yaw;
	motors[2] = thrust - pitch + roll + yaw;
	motors[3] = thrust - pitch - roll - yaw;
}

