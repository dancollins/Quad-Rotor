/*
	Quad Rotor Flight Controller
	file: accel.c
	author: Dan Collins
	date: July 10
*/

#include <ch.h>
#include <hal.h>

#include "accel.h"

#include "debug.h"

Accel accel; // Create an accel struct for storing values

static i2cblock_t accel_tx[8]; // Two bytes get transmitted at one time (Register and Value)
static i2cblock_t accel_rx[8]; // Up to eight bytes get received TODO: Tune number of bytes

static void accel_err(I2CDriver *i2cp, const I2CSlaveConfig *i2cscfg) {
	(void) i2cscfg;
	int status = 0;
	status = i2cp->id_i2c->SR1;
	debug_println("Accelerometer: Callback Error...");
	while(1);
}

static void accel_callback(I2CDriver *i2cd, const I2CSlaveConfig *i2cscfg) {
	(void) i2cd;
	(void) i2cscfg;
}

static const I2CSlaveConfig accel_cfg = {
	accel_callback,
	accel_err,
};

int accel_init(void) {
	/* Set the unit to measure mode */
	accel_tx[0] = POWER_CTL;
	accel_tx[1] = MEASURE;
	
	i2cMasterTransmit(&I2CD1, &accel_cfg, accel_addr, accel_tx, 2, accel_rx, 0);
	
	chThdSleepMilliseconds(100); // TODO: Tune.  Needs delay to allow for a transfer!
	
	/* Set range to +-4g */
	accel_tx[0] = DATA_FORMAT;
	accel_tx[1] = RANGE_0;
	
	i2cMasterTransmit(&I2CD1, &accel_cfg, accel_addr, accel_tx, 2, accel_rx, 0);
	
	return 0;
}

void accel_read(void) {
	accel_tx[0] = DATAX0; // Address of first byte...
	
	i2cMasterTransmit(&I2CD1, &accel_cfg, accel_addr, accel_tx, 1, accel_rx, 6);
	
	accel.x = accel_rx[0] + (accel_rx[1] << 8);
	accel.y = accel_rx[2] + (accel_rx[3] << 8);
	accel.z = accel_rx[4] + (accel_rx[5] << 8);
}

