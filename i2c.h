/*
 * Quad Rotor Controller
 * Rev A
 * Dan Collins 2012
 */

#ifndef I2C_H
#define I2C_H

#include <plib.h>

BOOL i2c_start_transfer(BOOL restart);
BOOL i2c_send_byte(unsigned char c);
unsigned char i2c_get_byte(BOOL ack);
BOOL i2c_stop_transfer(void);

#endif