/*
 * Quad Rotor Base Station
 * file: hardware.h
 * author: Dan Collins
 * created: 28/08/11
 * file description:
 *      Used to tidy up the init(); function in main.c by holding a bunch of
 *      TRIS masks.
 */

#ifndef HARDWARE_H
#define HARDWARE_H

// Port A
// RA0 - Key Switch
// RA1 - Unassigned
// RA2 - Unassigned
// RA3 - Unassigned
// RA4 - Unassigned
#define tris_a 0x01;

// Port B
// RB0 - Unassigned
// RB1 - Unassigned
// RB2 - Unassigned
// RB3 - Unassigned
// RB4 - Unassigned
// RB5 - Output LED
// RB6 - UART1 Rx
// RB7 - UART1 Tx
// RB8 - Unassigned
// RB9 - Unassigned
// RB10 - Unassigned
// RB11 - Unassigned
// RB12 - Unassigned
// RB13 - Unassigned
// RB14 - UART2 Rx
// RB15 - UART2 Tx
#define tris_b 0xffdf;

#endif
