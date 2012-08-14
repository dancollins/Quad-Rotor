// HardwareProfile.h

#ifndef _HARDWARE_PROFILE_H_
#define _HARDWARE_PROFILE_H_

#include <p32xxxx.h>
#include <plib.h>
#include <stdio.h>


// CPU Clock
#define GetSystemClock()            80000000UL
#define GetPeripheralClock()        40000000UL
#define GetInstructionClock()       (GetSystemClock() / 2) ??? // Not sure what the '???' is for...!

// LEDs
#define LED_ON() LATBbits.LATB15 = 1
#define LED_OFF() LATBbits.LATB15 = 0
#define LED_TOGGLE() LATBbits.LATB15 ^= 1
#define LED TRISBbits.TRISB15

// PWM
#define PWM_PRESCALE 64
#define PWM_FREQUENCY 50
#define PWM_TICK (GetPeripheralClock()/PWM_PRESCALE/PWM_FREQUENCY)

#define MOTORA TRISDbits.TRISD0
#define MOTORB TRISDbits.TRISD1
#define MOTORC TRISDbits.TRISD2
#define MOTORD TRISDbits.TRISD3

#define timeToPeriod(x) x/1.6


#endif

