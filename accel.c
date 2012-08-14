/*
 * Quad Rotor Controller
 * Rev A
 * Dan Collins 2012
 */

#include "accel.h"

void accel_init(void) {
    I2C_7_BIT_ADDRESS addr;

    I2C_FORMAT_7_BIT_ADDRESS(addr, accel_addr, I2C_WRITE);

    i2c_start_transfer(FALSE);
    i2c_send_byte(I2C_GET_7_BIT_ADDRESS_BYTE(addr)); // Send slave address + w
    i2c_send_byte(acPOWER_CTL); // Power control register
    i2c_send_byte(acMEASURE); // Set to measurement mode
    i2c_stop_transfer(); // Stop signal

    i2c_start_transfer(FALSE); // Start signal
    i2c_send_byte(I2C_GET_7_BIT_ADDRESS_BYTE(addr)); // Send slave address + w
    i2c_send_byte(acDATA_FORMAT); // Data format register
    i2c_send_byte(acRANGE_0); // Set the measurement range to +-2g
    i2c_stop_transfer(); // Stop signal
}
void accel_read(struct accelData *accel) {
    unsigned char xl, xh, yl, yh, zl, zh; // 8 bit data variables

    StartI2C1();
    IdleI2C1();

    MasterWriteI2C1((accel_addr<<1) | 0);
    IdleI2C1();
    MasterWriteI2C1(acDATAX0);
    IdleI2C1();

    RestartI2C1();
    IdleI2C1();

    MasterWriteI2C1((accel_addr<<1) | 1);
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

    /* Put the data into integers.  X and Z axes are swapped. */
    accel->z = xl | (xh << 8);
    accel->y = yl | (yh << 8);
    accel->x = zl | (zh << 8);

    StopI2C1();
    IdleI2C1();
}
