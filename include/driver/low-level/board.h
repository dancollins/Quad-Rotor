/**
 * @author: Dan
 * @since November 24, 2012, 3:04 PM
 * @version 1.0
 *
 * Controls low-level access to the board itself.
 * Will also prepare the board for use by the main application
 */

#ifndef BOARD_H
#define BOARD_H

#include <xc.h>
#include <GenericTypeDefs.h>
#include <plib.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "serial.h"

/**
 * System
 */
#define PBDIV 2 // Peripheral clock divider

#define GetSystemClock() 80000000ul
#define GetPeripheralClock() GetSystemClock() / PBDIV
#define GetInstructionClock() GetSystemClock()

/**
 * LEDs
 */
// Call this to prepare the LED
#define init_led1() TRISGbits.TRISG12 = 0
#define init_led2() TRISGbits.TRISG13 = 0
#define init_led3() TRISGbits.TRISG14 = 0
#define init_led4() TRISGbits.TRISG15 = 0
#define init_led5() TRISBbits.TRISB2 = 0
#define init_led6() TRISBbits.TRISB3 = 0
#define init_led7() TRISBbits.TRISB4 = 0
#define init_led8() TRISBbits.TRISB6 = 0
#define init_led9() TRISBbits.TRISB7 = 0
#define init_led10() TRISBbits.TRISB8 = 0
#define init_led11() TRISBbits.TRISB9 = 0
#define init_led12() TRISBbits.TRISB10 = 0
// Call this to turn the LED on/off
#define led1 LATGbits.LATG12
#define led2 LATGbits.LATG13
#define led3 LATGbits.LATG14
#define led4 LATGbits.LATG15
#define led5 LATBbits.LATB2
#define led6 LATBbits.LATB3
#define led7 LATBbits.LATB4
#define led8 LATBbits.LATB6
#define led9 LATBbits.LATB7
#define led10 LATBbits.LATB8
#define led11 LATBbits.LATB9
#define led12 LATBbits.LATB10
// Call this to sleep the LED (Put it into a low power mode)
#define sleep_led1() led1 = 0; TRISGbits.TRISG12 = 1
#define sleep_led2() led2 = 0; TRISGbits.TRISG13 = 1
#define sleep_led3() led3 = 0; TRISGbits.TRISG14 = 1
#define sleep_led4() led4 = 0; TRISGbits.TRISG15 = 1
#define sleep_led5() led5 = 0; TRISBbits.TRISB2 = 1
#define sleep_led6() led6 = 0; TRISBbits.TRISB3 = 1
#define sleep_led7() led7 = 0; TRISBbits.TRISB4 = 1
#define sleep_led8() led8 = 0; TRISBbits.TRISB6 = 1
#define sleep_led9() led9 = 0; TRISBbits.TRISB7 = 1
#define sleep_led10() led10 = 0; TRISBbits.TRISB8 = 1
#define sleep_led11() led11 = 0; TRISBbits.TRISB9 = 1
#define sleep_led12() led12 = 0; TRISBbits.TRISB10 = 1

/**
 * Buttons
 */
// Call this to prepare the button
#define init_but1() TRISGbits.TRISG6 = 1
#define init_but2() TRISGbits.TRISG7 = 1
#define init_but3() TRISAbits.TRISA0 = 1
// Call this to read the state of the button
#define but1 PORTGbits.RG6
#define but2 PORTGbits.RG7
#define but3 PORTAbits.RA0
// This is the number of ticks a button needs to be held down
#define BUTTON_COUNT 30

typedef struct {
    BOOL pressed; // True when the button is pressed
    BYTE read; // True when the button has been read
    BYTE time; // The length of the press
} button_t;

/**
 * Set up the peripherals on the board
 */
void board_init(void);

/**
 * This needs to be run at the tick rate to update the board
 */
void board_update(void * pvParameters);

/**
 * Send the CPU into idle mode
 */
void board_idle(void);

/**
 * Get the state of the given button
 * @param button The button to check (1, 2, 3)
 * @return The state of the button
 */
BOOL board_getButtonState(BYTE button);

#endif
