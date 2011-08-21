/*
	Quad Rotor Flight Controller
	file: i2cdriver.c
	author: Dan Collins
	date: July 10
*/

#include <ch.h>
#include <hal.h>

#include "i2cdriver.h"

#include "accel.h"
//#include "gyro.h"

#include "debug.h"

static const I2CConfig i2c_conf = {
	OPMODE_I2C, // I2C Mode
	50000, // 50KHz CLK
	STD_DUTY_CYCLE, // Standard duty cycle (not fast duty cycle)
	0, // 7bit address
	0, // Extra bits of 10bit address
	0, // Enable/disable acknowledgemet
	0, // Enable/disable 7/10bit acknowledgement
};

void i2cdriver_init(void) {
	debug_print("Starting I2C...");
	i2cStart(&I2CD1, &i2c_conf); // Start the I2C1 driver
	debug_println("Done");
	
	debug_print("Starting Accel...");
	accel_init(); // Prepare the accelerometer
	debug_println("Done");
	chThdSleepMilliseconds(100); // May not be needed.  Using as in example code.
	
	debug_print("Starting Gyro...");
	gyro_init(); // Prepare the gyroscope
	debug_println("Done");
	chThdSleepMilliseconds(100); // Also may not be needed.
}
