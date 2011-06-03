/*
	Quad Rotor Flight Controller
	file: serial.h
	author: Dan Collins
	date: June 03
*/
#ifndef SERIAL_H
#define SERIAL_H

extern BaseChannel *chp;

void serial_print(const char *msg); // Prints *msg to the BaseChannel chp as defined in main.c
void serial_println(const char *msg); // Same as serial_print, but also prints line feed
void serial_printn(uint32_t n); // Prints an integer as ASCII

#endif
