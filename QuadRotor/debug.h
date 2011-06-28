/*
	Quad Rotor Flight Controller
	file: debug.h
	author: Dan Collins
	date: June 03
*/
#ifndef DEBUG_H
#define DEBUG_H

extern BaseChannel *console;

void debug_print(const char *msg); // Prints *msg to the BaseChannel chp as defined in main.c
void debug_println(const char *msg); // Same as serial_print, but also prints line feed
void debug_printn(uint32_t n); // Prints an integer as ASCII

#endif
