/*
	Quad Rotor Flight Controller
	file: radio.h
	author: Dan Collins
	date: June 03
*/
#ifndef RADIO_H
#define RADIO_H

#include <ch.h>
#include <hal.h>

extern BaseChannel *radio;

static void txend1 (UARTDriver *uartp); // Buffer is completely read by driver
static void txend2 (UARTDriver *uartp); // Buffer has been physically sent
static void rxerr (UARTDriver *uartp, uartflags_t e); // Receive Error (mask is passed)
static void rxchar (UARTDriver *uartp, uint16_t c); // Character received, but application isn't ready to receive
static void rxend (UARTDriver *uartp); // Receive buffer is completely written

void radio_init(void);
void radio_print(const char *msg);

#endif
