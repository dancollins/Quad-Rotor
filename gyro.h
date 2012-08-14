/*
 * Quad Rotor Controller
 * Rev A
 * Dan Collins 2012
 */

#ifndef GYRO_H
#define GYRO_H

#include "HardwareProfile.h"
#include "i2c.h"

#define gyro_addr 0x68

/* ITG3200 Registers */
#define gyWHO_AM_I 0x00
#define gySMPLRT_DIV 0x15
#define gyDLPF_FS 0x16
#define gyINT_CFG 0x17
#define gyINT_STATUS 0x1A
#define gyTEMP_OUT_H 0x1B
#define gyTEMP_OUT_L 0x1C
#define gyGYRO_XOUT_H 0x1D
#define gyGYRO_XOUT_L 0x1E
#define gyGYRO_YOUT_H 0x1F
#define gyGYRO_YOUT_L 0x20
#define gyGYRO_ZOUT_H 0x21
#define gyGYRO_ZOUT_L 0x22
#define gyPWR_MGM 0x3E

//Sample Rate Divider
//Fsample = Fint / (divider + 1) where Fint is either 1kHz or 8kHz
//Fint is set to 1kHz
//Set divider to 9 for 100 Hz sample rate

//DLPF, Full Scale Register Bits
//FS_SEL must be set to 3 for proper operation
//Set DLPF_CFG to 3 for 1kHz Fint and 42 Hz Low Pass Filter
#define gyDLPF_CFG_0 (1<<0)
#define gyDLPF_CFG_1 (1<<1)
#define gyDLPF_CFG_2 (1<<2)
#define gyDLPF_FS_SEL_0 (1<<3)
#define gyDLPF_FS_SEL_1 (1<<4)

//Power Management Register Bits
//Recommended to set CLK_SEL to 1,2 or 3 at startup for more stable clock
#define gyPWR_MGM_CLK_SEL_0 (1<<0)
#define gyPWR_MGM_CLK_SEL_1 (1<<1)
#define gyPWR_MGM_CLK_SEL_2 (1<<2)
#define gyPWR_MGM_STBY_Z (1<<3)
#define gyPWR_MGM_STBY_Y (1<<4)
#define gyPWR_MGM_STBY_X (1<<5)
#define gyPWR_MGM_SLEEP (1<<6)
#define gyPWR_MGM_H_RESET (1<<7)

//Interrupt Configuration Bist
#define gyINT_CFG_ACTL (1<<7)
#define gyINT_CFG_OPEN (1<<6)
#define gyINT_CFG_LATCH_INT_EN (1<<5)
#define gyINT_CFG_INT_ANYRD (1<<4)
#define gyINT_CFG_ITG_RDY_EN (1<<2)
#define gyINT_CFG_RAW_RDY_EN (1<<0)

struct gyroData {
    short x;
    short y;
    short z;
};


void gyro_init(void); // Prepares the gyroscope for measurements
void gyro_read(struct gyroData *gyro); // Read data from the gyroscope

#endif
