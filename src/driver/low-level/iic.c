#include "iic.h"

void iic_init(void) {
    I2CConfigure(I2C2, I2C_ENABLE_HIGH_SPEED);
    I2CSetFrequency(I2C2, GetPeripheralClock(), 400000); // 400KHz
    I2CEnable(I2C2, TRUE);
}

BOOL iic_start(BYTE p, BOOL restart) {
    I2C_RESULT result;

    // Send the condition
    if (restart == TRUE) {
        result = I2CRepeatStart(p);
    } else {
        while (I2CBusIsIdle(p) == FALSE); // Wait for the bus to be idle
        result = I2CStart(p);
    }

    // Check the condition can be sent
    if (result != I2C_SUCCESS)
        return FALSE;

    // Wait for the condition to finish sending
    while ((I2CGetStatus(p) & I2C_START) == FALSE);

    return TRUE;
}

BOOL iic_stop(BYTE p) {
    I2CStop(p); // Send the stop condition

    // Wait for the condition to finish sending
    while ((I2CGetStatus(p) & I2C_STOP) == FALSE);

    return TRUE;
}

BOOL iic_sendByte(BYTE p, BYTE b) {
    I2C_RESULT result;
    
    while (I2CTransmitterIsReady(p) == FALSE); // Wait for the transmitter to be ready

    result = I2CSendByte(p, b); // Send the byte to the module
    if (result == I2C_MASTER_BUS_COLLISION) // Check the send didn't cause a collision
        return FALSE;

    while (I2CTransmissionHasCompleted(p) == FALSE); // Wait for the byte to finish sending

    return TRUE;
}

BYTE iic_getByte(BYTE p, BOOL ack) {
    I2CReceiverEnable(p, TRUE);

    while(I2CReceivedDataIsAvailable(p) == FALSE); // Wait for a byte to be received

    I2CAcknowledgeByte(p, ack); // Send an ACK / NACK
    while(!I2CAcknowledgeHasCompleted(p)); // Wait for the ACK / NACK to send

    return I2CGetByte(p); // Return the received byte
}
