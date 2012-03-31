#ifndef ITG3200_H
#define ITG3200_H

#include "i2c.h"

class ITG3200 {
	private:
		I2C& i2c;
	
	public:
		int16_t x, y, z;
		
		ITG3200(I2C& i2c_bus) : i2c(i2c_bus) {
			
		}
		
		void init() {
			i2c.write_reg(0x68, 0x3e, 0x03); // Select clock reference.
			i2c.write_reg(0x68, 0x16, 0x18 | 0x02); // 2000 deg/sec range, 98 Hz bandwidth.
		}
		
		void update() {
			uint8_t buf[6];
			i2c.read_reg(0x68, 0x1d, 6, buf);
			
			x = (buf[0] << 8 | buf[1]) - 0;
			y = (buf[2] << 8 | buf[3]) - 0;
			z = (buf[4] << 8 | buf[5]) - 0;
		}
};

#endif
