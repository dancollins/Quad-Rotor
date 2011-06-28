/*
	Quad Rotor Flight Controller
	file: radio.c
	author: Dan Collins
	date: June 03
*/
#include <ch.h>
#include <hal.h>

#include "radio.h"

/*
 * This callback is invoked when a transmission buffer has been completely
 * read by the driver.
 */
static void txend1(UARTDriver *uartp) {
	(void)uartp;
}

/*
 * This callback is invoked when a transmission has phisically completed.
 */
static void txend2(UARTDriver *uartp) {
	(void)uartp;
}

/*
 * This callback is invoked on a receive error, the errors mask is passed
 * as parameter.
 */
static void rxerr(UARTDriver *uartp, uartflags_t e) {
	(void)uartp;
	(void)e;
}

/*
 * This callback is invoked when a character is received but the application
 * was not ready to receive it, the character is passed as parameter.
 */
static void rxchar(UARTDriver *uartp, uint16_t c) {
	(void)uartp;
	(void)c;
}

/*
 * This callback is invoked when a receive buffer has been completely written.
 */
static void rxend(UARTDriver *uartp) {
	(void)uartp;
}

static UARTConfig uart_cfg = {
	txend1, // End of transmission buffer
	txend2, // Physical end of transmission
	rxend, // RX buffer filled
	rxchar, // Char received while out of buffer receive state
	rxerr, // RX error callback
	9600, // 9600 bps
	0, // No special configuration
	0,
	0
};

void radio_init(void) {
	uartStart(&UARTD3, &uart_cfg);
	//radio = &UARTD3; // Use SerialDriver3 as radio output
}

void radio_print(const char *msg) {
  while (*msg)
    chIOPut(radio, *msg++);
}

void radio_println(const char *msg) {
	/*radio_print(msg);
	chIOPut(radio, '\n');*/
	uartStartSend(&UARTD3, 14, "Hello World!\r\n");
}
