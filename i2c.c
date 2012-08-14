/*
 * Quad Rotor Controller
 * Rev A
 * Dan Collins 2012
 */

#include "i2c.h"

BOOL i2c_start_transfer(BOOL restart) {
    I2C_STATUS status;

    if (restart)
        I2CRepeatStart(I2C1); // Send a repeat start condition
    else {
        while (!I2CBusIsIdle(I2C1)); // Wait for the bus to be idle
        if (I2CStart(I2C1) != I2C_SUCCESS) // Send a start condition
            return FALSE; // An error occured, so return false
    }

    do {
        status = I2CGetStatus(I2C1); // Wait for the start condition to be sent
    } while (!(status & I2C_START));
    return TRUE; // Success, so return true
}

BOOL i2c_send_byte(unsigned char c) {
    while (!I2CTransmitterIsReady(I2C1)); // Wait until the transmitter is ready
    if (I2CSendByte(I2C1, c) == I2C_MASTER_BUS_COLLISION) // Send the byte, and check that it didn't cause a collision
        return FALSE; // Collision occured, so return false
    while (!I2CTransmissionHasCompleted(I2C1)); // Wait for the byte to have sent
    return TRUE; // Succes, so return true
}

unsigned char i2c_get_byte(BOOL ack) {
    while(!I2CReceivedDataIsAvailable(I2C1));
    I2CAcknowledgeByte(I2C1, ack);
    while(!I2CAcknowledgeHasCompleted(I2C1));
    return I2CGetByte(I2C1);
}

BOOL i2c_stop_transfer(void) {
    I2C_STATUS status;

    I2CStop(I2C1); // Send stop condition

    do {
        status = I2CGetStatus(I2C1); // Wait for the stop condition to be sent
    } while (!(status & I2C_STOP));
}
