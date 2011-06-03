/*
	Quad Rotor Flight Controller
	file: serial.c
	author: Dan Collins
	date: June 03
*/
#include <ch.h>
#include <hal.h>

#include "serial.h"

void serial_print(const char *msg) {
  while (*msg)
    chIOPut(chp, *msg++);
}

void serial_println(const char *msg) {
	serial_print(msg);
	chIOPut(chp, '\n');
}

void serial_printn(uint32_t n) {
	char buf[16], *p;

	if (!n) {
		chIOPut(chp, '0');
	} else {
		p = buf;
		while (n) {
			*p++ = (n % 10) + '0', n /= 10;
		}
		while (p > buf) {
			chIOPut(chp, *--p);
		}
	}
}
