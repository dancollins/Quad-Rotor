/*
	Quad Rotor Flight Controller
	file: gyro.c
	author: Dan Collins
	date: August 20
*/

#include <ch.h>
#include <hal.h>

#include "gyro.h"

#include "debug.h"

Gyro gyro; // Create a gyro struct for storing values

static i2cblock_t gyro_tx[8]; // Two bytes get transmitted at one time (Register and Value)
static i2cblock_t gyro_rx[8]; // Up to eight bytes get received TODO: Tune number of bytes

static void gyro_err(I2CDriver *i2cp, const I2CSlaveConfig *i2cscfg) {
	(void) i2cscfg;
	int status = 0;
	status = i2cp->id_i2c->SR1;
	debug_println("Gyroscope: Callback Error...");
	while(1);
}

static void gyro_callback(I2CDriver *i2cd, const I2CSlaveConfig *i2cscfg) {
	(void) i2cd;
	(void) i2cscfg;
}

static const I2CSlaveConfig gyro_cfg = {
	gyro_callback,
	gyro_err,
};

int gyro_init(void) {
	/* Use Z gyro for clock */
	gyro_tx[0] = PWR_MGM;
	gyro_tx[1] = PWR_MGM_CLK_SEL_0 | PWR_MGM_CLK_SEL_1;
	
	i2cMasterTransmit(&I2CD1, &gyro_cfg, gyro_addr, gyro_tx, 2, gyro_rx, 0);
	
	chThdSleepMilliseconds(100); // TODO: Tune.  Needs delay to allow for a transfer!
	
	/* Set 2000deg/sec output, and 98Hz Operation */
	gyro_tx[0] = DLPF_FS;
	gyro_tx[1] = DLPF_FS_SEL_0 | DLPF_FS_SEL_1 | DLPF_CFG_1;
	
	i2cMasterTransmit(&I2CD1, &gyro_cfg, gyro_addr, gyro_tx, 2, gyro_rx, 0);
	
	return 0;
}

void gyro_read(void) {
	gyro_tx[0] = GYRO_XOUT_H; // Address of first byte...
	
	i2cMasterTransmit(&I2CD1, &gyro_cfg, gyro_addr, gyro_tx, 1, gyro_rx, 6);
	
	gyro.x = gyro_rx[0] + (gyro_rx[1] << 8);
	gyro.y = gyro_rx[2] + (gyro_rx[3] << 8);
	gyro.z = gyro_rx[4] + (gyro_rx[5] << 8);
}

