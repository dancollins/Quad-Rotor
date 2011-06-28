/*
	Quad Rotor Flight Controller
	file: radio.c
	author: Dan Collins
	date: June 03
*/
#include <ch.h>
#include <hal.h>

#include <string.h>

#include "radio.h"
#include "debug.h"

VirtualTimer vt1;

static void ledoff(void *p) {
	(void)p;
	palSetPad(IOPORT2, GPIOB_LED2);
}

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
	debug_println(c);
	palClearPad(IOPORT2, GPIOB_LED2);
	chSysLockFromIsr();
	if (chVTIsArmedI(&vt1))
		chVTResetI(&vt1);
	chVTSetI(&vt1, MS2ST(100), ledoff, NULL);
	chSysUnlockFromIsr();
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
}

void radio_print(const char *msg) {
    uartStartSend(&UARTD3, strlen(msg), msg);
}

