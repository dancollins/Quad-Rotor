#include "accel.h"

void accel_init(void) {
    /* Set the accelerometer to output at 100Hz */
    iic_start(acMODULE, FALSE); // Start
    iic_sendByte(acMODULE, acADDR); // Send write address
    iic_sendByte(acMODULE, acBW_RATE); // Power control register
    iic_sendByte(acMODULE, 0x0A); // 100Hz output rate
    iic_stop(acMODULE); // Stop

    /* Set the accelerometer to measure mode */
    iic_start(acMODULE, FALSE); // Start
    iic_sendByte(acMODULE, acADDR); // Send write address
    iic_sendByte(acMODULE, acPOWER_CTL); // Power control register
    iic_sendByte(acMODULE, acMEASURE); // Allow the accelerometer to take measurements
    iic_stop(acMODULE); // Stop

    /* Set up the output range for +-2g */
    iic_start(acMODULE, FALSE); // Start
    iic_sendByte(acMODULE, acADDR); // Send write address
    iic_sendByte(acMODULE, acDATA_FORMAT); // Data format register
    iic_sendByte(acMODULE, acRANGE_0); // +-2g
    iic_stop(acMODULE); // Stop

    /* Allow data ready to create an interrupt */
    iic_start(acMODULE, FALSE); // Start
    iic_sendByte(acMODULE, acADDR); // Send write address
    iic_sendByte(acMODULE, acINT_ENABLE); // Interrupt enable
    iic_sendByte(acMODULE, acDATA_READY); // Data ready
    iic_stop(acMODULE); // Stop

    /* Configure the interrupt pin */
    iic_start(acMODULE, FALSE); // Start
    iic_sendByte(acMODULE, acADDR); // Send write address
    iic_sendByte(acMODULE, acINT_MAP); // Interrupt configuration register
    iic_sendByte(acMODULE, 0); // Only use the one interrupt pin
    iic_stop(acMODULE); // Stop
}

void accel_read(AccelData_t * data) {
    SHORT x, y, z; // Hold the data straight out of the gyro

    iic_start(acMODULE, FALSE);
    iic_sendByte(acMODULE, acADDR);
    iic_sendByte(acMODULE, acDATAX0);

    iic_start(acMODULE, TRUE);
    iic_sendByte(acMODULE, acADDR | 1);

    /* X */
    x = (iic_getByte(acMODULE, TRUE)<<8);
    x |= iic_getByte(acMODULE, TRUE);

    /* Y */
    y = (iic_getByte(acMODULE, TRUE)<<8);
    y |= iic_getByte(acMODULE, TRUE);

    /* Z */
    z = (iic_getByte(acMODULE, TRUE)<<8);
    z |= iic_getByte(acMODULE, FALSE);

    iic_stop(acMODULE);

    data->x = x * 0.0039;
    data->y = y * 0.0039;
    data->z = z * 0.0039;
}

