/*
 * Quad Rotor Controller
 * Rev A
 * Dan Collins 2012
 */

#include "gyro.h"

void gyro_init(void) {
    I2C_7_BIT_ADDRESS addr;

    I2C_FORMAT_7_BIT_ADDRESS(addr, gyro_addr, I2C_WRITE);

    i2c_start_transfer(FALSE);
    i2c_send_byte(I2C_GET_7_BIT_ADDRESS_BYTE(addr)); // Send slave address + w
    i2c_send_byte(gyPWR_MGM); // Power management register
    i2c_send_byte(gyPWR_MGM_CLK_SEL_0 | gyPWR_MGM_CLK_SEL_1); // Set up clock TODO: Better comment
    i2c_stop_transfer(); // Stop signal

    i2c_start_transfer(FALSE); // Start signal
    i2c_send_byte(I2C_GET_7_BIT_ADDRESS_BYTE(addr)); // Send slave address + w
    i2c_send_byte(gyDLPF_FS); // Full scale register
    i2c_send_byte(gyDLPF_FS_SEL_0 | gyDLPF_FS_SEL_1 | gyDLPF_CFG_1); // 2000°/s @ 98Hz
    i2c_stop_transfer(); // Stop signal
}

void gyro_read(struct gyroData *gyro) {
    unsigned char xl, xh, yl, yh, zl, zh; // 8 bit data variables

    StartI2C1();
    IdleI2C1();

    MasterWriteI2C1((gyro_addr<<1) | 0);
    IdleI2C1();
    MasterWriteI2C1(gyGYRO_XOUT_H);
    IdleI2C1();

    RestartI2C1();
    IdleI2C1();

    MasterWriteI2C1((gyro_addr<<1) | 1);
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
    gyro->z = xl | (xh << 8);
    gyro->y = yl | (yh << 8);
    gyro->x = zl | (zh << 8);

    StopI2C1();
    IdleI2C1();
}
