/*
	Quad Rotor Flight Controller
	file: accel.h
	author: Dan Collins
	date: July 10
*/
#ifndef ACCEL_H
#define ACCEL_H

#define accel_addr 0x53 // (0x53<<1) = 0xA6

/* ADXL Registers */
#define DEVID               0x00 // Device ID register
#define THRESH_TAP          0x1D // Tap threshold
#define OFSX                0x1E // X-axis offset
#define OFSY                0x1F // Y-axis offset
#define OFSZ                0x20 // Z-axis offset
#define DUR                 0x21 // Tap duration
#define Latent              0x22 // Tap latency
#define Window              0x23 // Tap window
#define THRESH_ACT          0x24 // Activity threshold
#define THRESH_INACT        0x25 // Inactivity threshold
#define TIME_INACT          0x26 // Inactivity time
#define ACT_INACT_CTL       0x27 // Axis enable control for activity and inactivity detection
#define THRESH_FF           0x28 // Free-fall threshold
#define TIME_FF             0x29 // Free-fall time
#define TAP_AXES            0x2A // Axis control for tap/double tap
#define ACT_TAP_STATUS      0x2B // Source of tap/double tap
#define BW_RATE             0x2C // Data rate and power mode control
#define POWER_CTL           0x2D // Power control register
#define INT_ENABLE          0x2E // Interrupt enable control
#define INT_MAP             0x2F // Interrupt mapping control
#define INT_SOURCE          0x30 // Source of interrupts
#define DATA_FORMAT         0x31 // Data format control
#define DATAX0              0x32 // X-Axis data 0
#define DATAX1              0x33 // X-Axis data 1
#define DATAY0              0x34 // Y-Axis data 0
#define DATAY1              0x35 // Y-Axis data 1
#define DATAZ0              0x36 // Z-Axis data 0
#define DATAZ1              0x37 // Z-Axis data 1
#define FIFO_CTL            0x38 // FIFO control
#define FIFO_STATUS         0x39 // FIFO status


/* ADXL Values */
//Power Control Register Bits
#define WU_0                (1<<0) //Wake Up Mode - Bit 0
#define WU_1                (1<<1) //Wake Up mode - Bit 1
#define SLEEP               (1<<2) //Sleep Mode
#define MEASURE             (1<<3) //Measurement Mode
#define AUTO_SLP            (1<<4) //Auto Sleep Mode bit
#define LINK                (1<<5) //Link bit

//Interrupt Enable/Interrupt Map/Interrupt Source Register Bits
#define OVERRUN             (1<<0)
#define WATERMARK           (1<<1)
#define FREE_FALL           (1<<2)
#define INACTIVITY          (1<<3)
#define ACTIVITY            (1<<4)
#define DOUBLE_TAP          (1<<5)
#define SINGLE_TAP          (1<<6)
#define DATA_READY          (1<<7)

//Data Format Bits
#define RANGE_0             (1<<0)
#define RANGE_1             (1<<1)
#define JUSTIFY             (1<<2)
#define FULL_RES            (1<<3)

typedef struct accelData {
	int16_t x;
	int16_t y;
	int16_t z;
} Accel;

extern Accel accel;

static void accel_err(I2CDriver *i2cd, const I2CSlaveConfig *i2cscfg); // Error callback
static void accel_callback(I2CDriver *i2cd, const I2CSlaveConfig *i2cscfg); // Data callback
int accel_init(void); // Prepares the accelerometer for measurements
void accel_read(void); // Read data from the accelerometer

#endif
