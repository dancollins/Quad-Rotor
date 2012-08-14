/*
 * Quad Rotor Controller
 * Rev A
 * Dan Collins 2012
 */

#ifndef MAG_H
#define MAG_H

#include "HardwareProfile.h"
#include "i2c.h"

#define mag_addr 0x0E

/* MAG3110 registers */
#define maDR_STATUS 0x00
#define maMAG_XOUT_H 0x01
#define maMAG_XOUT_L 0x02
#define maMAG_YOUT_H 0x03
#define maMAG_YOUT_L 0x04
#define maMAG_ZOUT_H 0x05
#define maMAG_ZOUT_L 0x06
#define maWHO_AM_I 0x07
#define maSYSMOD 0x08
#define maMAG_XOFF_H 0x09
#define maMAG_XOFF_L 0x0A
#define maMAG_YOFF_H 0x0B
#define maMAG_YOFF_L 0x0C
#define maMAG_ZOFF_H 0x0D
#define maMAG_ZOFF_L 0x0E
#define maTEMP_OUT 0x0F
#define maCTRL_REG1 0x10
#define maCTRL_REG2 0x11

/* Status Register */
#define maSTAT_ZYXOW (1<<7)
#define maSTAT_ZOW (1<<6)
#define maSTAT_YOW (1<<5)
#define maSTAT_XOW (1<<4)
#define maSTAT_ZYXDR (1<<3)
#define maSTAT_ZDR (1<<2)
#define maSTAT_YDR (1<<1)
#define maSTAT_XDR (1<<0)

/* Control Register1 */
#define maCTRL1_DR2 (1<<7)
#define maCTRL1_DR1 (1<<6)
#define maCTRL1_DR0 (1<<5)
#define maCTRL1_OS1 (1<<4)
#define maCTRL1_OS0 (1<<3)
#define maCTRL1_FR (1<<2)
#define maCTRL1_TM (1<<1)
#define maCTRL1_AC (1<<0)

/* Control Register2 */
#define maCTRL2_AUTO_MRST (1<<7)
#define maCTRL2_RAW (1<<5)
#define maCTRL2_MAG_RST (1<<4)

typedef struct magData {
	short x;
	short y;
	short z;
} Mag;

extern Mag mag;

void mag_init(void); // Prepares the magnetometer for measurements
void mag_read(void); // Read data from the magnetometer

#endif
