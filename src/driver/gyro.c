#include "gyro.h"

void gyro_init(void) {
    /* Set up the gyro clock */
    iic_start(gyMODULE, FALSE); // Start
    iic_sendByte(gyMODULE, gyADDR); // Send write address
    iic_sendByte(gyMODULE, gyPWR_MGM); // Power management register
    iic_sendByte(gyMODULE, gyPWR_MGM_CLK_SEL_0 | gyPWR_MGM_CLK_SEL_1); // Use the Z-axis gyro as the reference for the clock
    iic_stop(gyMODULE); // Stop

    /* Set up the output range for 2000° / s  and a LPF of 98Hz */
    iic_start(gyMODULE, FALSE); // Start
    iic_sendByte(gyMODULE, gyADDR); // Send write address
    iic_sendByte(gyMODULE, gyDLPF_FS); // Digital LPF register
    iic_sendByte(gyMODULE, gyDLPF_FS_SEL_0 | gyDLPF_FS_SEL_1 | gyDLPF_CFG_1); // 2000°/s, 98Hz LPF
    iic_stop(gyMODULE); // Stop

    /* Set the internal sample rate divider to 100Hz */
    iic_start(gyMODULE, FALSE); // Start
    iic_sendByte(gyMODULE, gyADDR); // Send write address
    iic_sendByte(gyMODULE, gySMPLRT_DIV); // Digital LPF register
    iic_sendByte(gyMODULE, 9); // 100Hz
    iic_stop(gyMODULE); // Stop

    /* Configure the interrupts */
    iic_start(gyMODULE, FALSE); // Start
    iic_sendByte(gyMODULE, gyADDR); // Send write address
    iic_sendByte(gyMODULE, gyINT_CFG); // Interrupt configuration register
    iic_sendByte(gyMODULE, gyINT_CFG_LATCH_INT_EN | gyINT_CFG_INT_ANYRD | gyINT_CFG_RAW_RDY_EN); // Pin stays on until a register is read and will activate when data is available
    iic_stop(gyMODULE); // Stop
}

void gyro_read(GyroData_t * data) {
    iic_start(gyMODULE, FALSE);
    iic_sendByte(gyMODULE, gyADDR);
    iic_sendByte(gyMODULE, gyGYRO_XOUT_H);

    iic_start(gyMODULE, TRUE);
    iic_sendByte(gyMODULE, gyADDR | 1);

    /* X */
    data->x = (iic_getByte(gyMODULE, TRUE)<<8);
    data->x |= iic_getByte(gyMODULE, TRUE);

    /* Y */
    data->y = (iic_getByte(gyMODULE, TRUE)<<8);
    data->y |= iic_getByte(gyMODULE, TRUE);

    /* Z */
    data->z = (iic_getByte(gyMODULE, TRUE)<<8);
    data->z |= iic_getByte(gyMODULE, FALSE);

    iic_stop(gyMODULE);
}
