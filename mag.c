/*
 * Quad Rotor Controller
 * Rev A
 * Dan Collins 2012
 */

#include "mag.h"

Mag mag; // Create an instance of the accelerometer struct

void mag_init(void) { // Prepares the magnetometer for measurements
    I2C_7_BIT_ADDRESS addr;

    I2C_FORMAT_7_BIT_ADDRESS(addr, mag_addr, I2C_WRITE);

    i2c_start_transfer(FALSE);
    i2c_send_byte(I2C_GET_7_BIT_ADDRESS_BYTE(addr)); // Send slave address + w
    i2c_send_byte(maCTRL_REG2); // Control Register 2
    i2c_send_byte(maCTRL2_AUTO_MRST); // Makes the magnetometer reset after each aquisition
    i2c_stop_transfer(); // Stop signal

    i2c_start_transfer(FALSE); // Start signal
    i2c_send_byte(I2C_GET_7_BIT_ADDRESS_BYTE(addr)); // Send slave address + w
    i2c_send_byte(maCTRL_REG1); // Full scale register
    i2c_send_byte(maCTRL1_AC); // Enable magnetometer
    i2c_stop_transfer(); // Stop signal
}

void mag_read(void) { // Read data from the magnetometer
    unsigned char xl, xh, yl, yh, zl, zh; // 8 bit data variables

    StartI2C1();
    IdleI2C1();

    MasterWriteI2C1((mag_addr<<1) | 0);
    IdleI2C1();
    MasterWriteI2C1(maMAG_XOUT_H);
    IdleI2C1();

    RestartI2C1();
    IdleI2C1();

    MasterWriteI2C1((mag_addr<<1) | 1);
    IdleI2C1();

    xl = MasterReadI2C1();
    IdleI2C1();
    AckI2C1();
    IdleI2C1();
    xh = MasterReadI2C1();
    IdleI2C1();
    AckI2C1();
    IdleI2C1();
    yl = MasterReadI2C1();
    IdleI2C1();
    AckI2C1();
    IdleI2C1();
    yh = MasterReadI2C1();
    IdleI2C1();
    AckI2C1();
    IdleI2C1();
    zl = MasterReadI2C1();
    IdleI2C1();
    AckI2C1();
    IdleI2C1();
    zh = MasterReadI2C1();
    IdleI2C1();
    NotAckI2C1();
    IdleI2C1();

    /* Put the data into integers */
    mag.x = xl | (xh << 8);
    mag.y = yl | (yh << 8);
    mag.z = zl | (zh << 8);

    StopI2C1();
    IdleI2C1();
}
