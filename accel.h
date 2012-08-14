/*
 * Quad Rotor Controller
 * Rev A
 * Dan Collins 2012
 */

#ifndef ACCEL_H
#define ACCEL_H

#include "HardwareProfile.h"
#include "i2c.h"

#define accel_addr 0x53

/* ADXL Registers */
#define acDEVID               0x00 // Device ID register
#define acTHRESH_TAP          0x1D // Tap threshold
#define acOFSX                0x1E // X-axis offset
#define acOFSY                0x1F // Y-axis offset
#define acOFSZ                0x20 // Z-axis offset
#define acDUR                 0x21 // Tap duration
#define acLatent              0x22 // Tap latency
#define acWindow              0x23 // Tap window
#define acTHRESH_ACT          0x24 // Activity threshold
#define acTHRESH_INACT        0x25 // Inactivity threshold
#define acTIME_INACT          0x26 // Inactivity time
#define acACT_INACT_CTL       0x27 // Axis enable control for activity and inactivity detection
#define acTHRESH_FF           0x28 // Free-fall threshold
#define acTIME_FF             0x29 // Free-fall time
#define acTAP_AXES            0x2A // Axis control for tap/double tap
#define acACT_TAP_STATUS      0x2B // Source of tap/double tap
#define acBW_RATE             0x2C // Data rate and power mode control
#define acPOWER_CTL           0x2D // Power control register
#define acINT_ENABLE          0x2E // Interrupt enable control
#define acINT_MAP             0x2F // Interrupt mapping control
#define acINT_SOURCE          0x30 // Source of interrupts
#define acDATA_FORMAT         0x31 // Data format control
#define acDATAX0              0x32 // X-Axis data 0
#define acDATAX1              0x33 // X-Axis data 1
#define acDATAY0              0x34 // Y-Axis data 0
#define acDATAY1              0x35 // Y-Axis data 1
#define acDATAZ0              0x36 // Z-Axis data 0
#define acDATAZ1              0x37 // Z-Axis data 1
#define acFIFO_CTL            0x38 // FIFO control
#define acFIFO_STATUS         0x39 // FIFO status


/* ADXL Values */
//Power Control Register Bits
#define acWU_0                (1<<0) //Wake Up Mode - Bit 0
#define acWU_1                (1<<1) //Wake Up mode - Bit 1
#define acSLEEP               (1<<2) //Sleep Mode
#define acMEASURE             (1<<3) //Measurement Mode
#define acAUTO_SLP            (1<<4) //Auto Sleep Mode bit
#define acLINK                (1<<5) //Link bit

//Interrupt Enable/Interrupt Map/Interrupt Source Register Bits
#define acOVERRUN             (1<<0)
#define acWATERMARK           (1<<1)
#define acFREE_FALL           (1<<2)
#define acINACTIVITY          (1<<3)
#define acACTIVITY            (1<<4)
#define acDOUBLE_TAP          (1<<5)
#define acSINGLE_TAP          (1<<6)
#define acDATA_READY          (1<<7)

//Data Format Bits
#define acRANGE_0             (1<<0)
#define acRANGE_1             (1<<1)
#define acJUSTIFY             (1<<2)
#define acFULL_RES            (1<<3)

struct accelData {
    short x;
    short y;
    short z;
};

void accel_init(void); // Prepares the accelerometer for measurements
void accel_read(struct accelData *accel); // Read data from the accelerometer

#endif