#ifndef ADXL345_H
#define ADXL345_H

#include "i2c.h"

#define accel_addr 0x53 // (0x53<<1) = 0xA6

#define POWER_CTL 0x2D // Power control register
#define BW_RATE 0x2C // Data rate and power mode control register
#define DATAX0 0x32 // X-Axis data 0 register

#define MEASURE (1<<3) //Measurement Mode

class ADXL345 {
	private:
		I2C& i2c;
	
	public:
		int16_t x, y, z;
		
		ADXL345(I2C& i2c_bus) : i2c(i2c_bus) {
			
		}
		
		void init() {
			i2c.write_reg(accel_addr, POWER_CTL, MEASURE); // Enable the measurements
			i2c.write_reg(accel_addr, BW_RATE, 0x08); // 25 Hz bandwidth
		}
		
		void update() {
			uint8_t buf[6];
			i2c.read_reg(accel_addr, DATAX0, 6, buf);
			
			x = (buf[1] << 8 | buf[0]) - 0;
			y = (buf[3] << 8 | buf[2]) - 0;
			z = (buf[5] << 8 | buf[4]) - 0;
		}
};

#endif
