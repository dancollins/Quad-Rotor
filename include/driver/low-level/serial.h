/**
 * @author: Dan
 * @since November 24, 2012, 3:52 PM
 * @version 1.0
 *
 * DESC
 */

#ifndef SERIAL_H
#define SERIAL_H

#include <xc.h>
#include <GenericTypeDefs.h>
#include <plib.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "board.h"

#define SERIAL_TX_BUFFER_SIZE 512 // The bytes in RAM that each buffer will ocupy (there is a Tx and an Rx buffer)
#define SERIAL_RX_BUFFER_SIZE 256 // The bytes in RAM that each buffer will ocupy (there is a Tx and an Rx buffer)

typedef struct {
    BYTE name; // The name of the module in plib.h

    /* TX Buffer */
    BYTE tx_buf[SERIAL_TX_BUFFER_SIZE]; // Bytes will be sent out from here
    BYTE tx_buf_index; // The current index of the sender
    BYTE tx_buf_size; // The number of bytes in the buffer

    /* RX Buffer */
    BYTE rx_buf[SERIAL_RX_BUFFER_SIZE];
    BYTE rx_buf_index; // The current index of the receiver
    BYTE rx_buf_size; // The number of bytes in the buffer
} SerialModule_t;

/**
 * Prepare the serial module
 */
void serial_init(void);

/**
 * Called by the interrupt to receive data into the serial buffer
 * @param p The port that called the interrupt
 */
void serial_isr(BYTE p);

/**
 * Handle the transmission of the output buffer
 * This needs to be called periodically to send bytes out of the buffer
 * @param p The port to process
 */
void serial_update(BYTE p);

/**
 * Put a single character into the transmit buffer
 * @param c The character to transmit
 * @return True if the byte was added
 */
BOOL serial_putChar(BYTE p, BYTE c);

/**
 * Put a string into the transmit buffer
 * @param s The string to transmit
 * @return True if the string was added
 */
BOOL serial_putString(BYTE p, BYTE *s);

/**
 * Put a fixed number of bytes into the output buffer
 * @param buf The buffer to add from
 * @param len The number of bytes in the buffer
 * @return True if the bytes were added
 */
BOOL serial_putData(BYTE p, BYTE *buf, DWORD len);

/**
 * Get a pointer to the receive buffer
 * @param p The port to get the buffer of
 * @return Pointer to the buffer
 */
BYTE * serial_getBuffer(BYTE p);

/**
 * Clear the receive buffer of the given port
 * @param p The port to clear
 */
void serial_clearBuffer(BYTE p);

/**
 * Load the struct for the given port.
 * @param p The UART port to reference
 * @return The structure or null
 */
SerialModule_t * serial_loadStruct(BYTE p);

#endif
