/**
 * @author: Dan
 * @since November 24, 2012, 5:05 PM
 * @version 1.0
 *
 * DESC
 */

#ifndef IIC_H
#define IIC_H

#include <xc.h>
#include <GenericTypeDefs.h>
#include <plib.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "board.h"

/**
 * Prepare the I2C module/s for use
 */
void iic_init(void);

/**
 * Send a start/restart condition
 * @param p The port to use
 * @param restart True to send a restart condition
 * @return True on success
 */
BOOL iic_start(BYTE p, BOOL restart);

/**
 * Send a stop condition
 * @param p The port to use
 * @return True on success
 */
BOOL iic_stop(BYTE p);

/**
 * Send a single byte
 * @param p The port to use
 * @param b The byte to send
 * @return True on success
 */
BOOL iic_sendByte(BYTE p, BYTE b);

/**
 * Get a byte
 * @param p The port to use
 * @param ack True to acknowledge the received byte
 * @return True on success
 */
BYTE iic_getByte(BYTE p, BOOL ack);

#endif
