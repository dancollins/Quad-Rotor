/*
 * Quad Rotor Base Station
 * file: main.c
 * author: Dan Collins
 * created: 28/08/11
 */

#define FCY 16000000UL // Clock Speed = 32MHz / 2

#include <p24Fxxxx.h>
#include <libpic30.h>
#include <stdlib.h>
#include <string.h>

#include "hardware.h"

_CONFIG2(FNOSC_FRCPLL & OSCIOFNC_ON & POSCMOD_NONE & I2C1SEL_PRI) // Internal FRC OSC = 8MHz
_CONFIG1(JTAGEN_OFF & GCP_OFF & GWRP_OFF & COE_OFF & FWDTEN_OFF & ICS_PGx1) //turn off junk we don't need

void _ISR _CNInterrupt(void); // Interrupt for pinchange
void _ISR _U1RXInterrupt(void); // Interrupt for bluetooth receive
void uart_putChar(char c, char p);
void uart_putString(const char *s, char p);
void clear_bt_buf(void);
int get_thrust(void); // Gets the thrust value from the bt buffer

volatile char unlock = 0; // System lock/unlock determined by this char

char bt_buf[100];
unsigned char bt_idx = 0;

void _ISR _CNInterrupt(void) {
    if (PORTAbits.RA0) {
        unlock = 1;
    } else if (!PORTAbits.RA0) {
        unlock = 0;
    }
    IFS1bits.CNIF = 0; // Clear flag
}

void _ISR _U1RXInterrupt(void) {
    char c = U1RXREG;
    if (c != 0x13) {
        bt_buf[bt_idx] = c;
        if (bt_idx<99) {
            bt_idx++;
        } else {
            bt_idx = 0;
        }
    }
    IFS0bits.U1RXIF = 0; // Clear flag
}

void init (void) {
    /* Oscillator */
    CLKDIVbits.RCDIV0=0; // Clock divider is 0
    OSCCONbits.SOSCEN=0; // Diable secondary oscillator

    /* Ports */
    TRISA = tris_a; // Defined in hardware.h
    TRISB = tris_b; // Defined in hardware.h
    AD1PCFG = 0xFFFF; // Default all pins to digital
    
    PORTA = 0x00; // Clear port
    PORTB = 0x00; // Clear port

    /* PPS */
    RPOR3 = (3<<8); // Set UART1 Tx to RP7 (RB7)
    RPINR18 = 6; // Set UART1 Rx to RP6 (RB6)
    RPOR7 = (5<<8); // Set UART2 Tx to RP15 (RB15)
    RPINR19 = 14; // Set UART2 Rx to RP14 (RB14)

    /* UART1 */
    U1BRG = 34; // 115200bps
    U1MODE = 0;
    U1MODEbits.BRGH = 1;
    U1STA = 0;
    U1MODEbits.UARTEN = 1;
    U1STAbits.UTXEN = 1;
    IFS0bits.U1RXIF = 0;

    /* UART2 */
    U2BRG = 103; // 9600bps
    U2STA = 0;
    U2MODEbits.UARTEN = 1;
    U2STAbits.UTXEN = 1;

    /* 
     * Interrupts
     */
    /* Pin Change*/
    CNEN1bits.CN2IE = 1; // Enable pin change interrupt on CN2 (RA0)
    IEC1bits.CNIE = 1; // Enable pin change interrupts
    IPC4bits.CNIP = 1; // Set CN interrupt to priority 1
    /* UART1 */
    IEC0bits.U1RXIE = 1; // Enable U1RX interrupt
    IPC2bits.U1RXIP = 2; // Set U1RX interrupt to priority 2

    clear_bt_buf();
}

int main(void) {
    init();
    int thrust = 0; // Holds thrust %age
    int old_thrust = 0; // Holds old thrust value.  Used to limit the number of bytes sent

    while(1) {
        if (unlock) { // If the safety switch is active
            LATBbits.LATB5 = 1; // Green LED
            thrust = get_thrust();
            clear_bt_buf();
            __delay_ms(5);
        } else { // System is locked!
            LATBbits.LATB5 = 0; // Red LED
            clear_bt_buf();
            thrust = 0;
        }
        if (thrust != old_thrust) {
            old_thrust = thrust;
            uart_putChar(thrust, 2);
        }
    }

    return 0;
}

void uart_putChar(char c, char p){
    switch (p) {
        case 1:
            while (U1STAbits.UTXBF); // Wait until there is room in the output buffer
            U1TXREG = c; // Transfer the character into the output buffer
            break;
        case 2:
            while (U2STAbits.UTXBF); // Wait until there is room in the output buffer
            U2TXREG = c; // Transfer the character into the output buffer
            break;
    }
    
}

void uart_putString(const char *s, char p){
    while(*s)
        uart_putChar(*s++, p); // Write a bunch of characters into the output buffer
}

void clear_bt_buf(void) {
    int i = 0;
    for (i=0; i<99; i++) {
        bt_buf[i] = 0;
    }
    bt_idx = 0;
}

int get_thrust(void) {
    char thrust[4]; // Hold ascii thrust
    int i = 0; // Temp index
    char *s; // Pointer to thrust string
    s = strstr(&bt_buf[0], "t"); // Find 't' in the buffer
    if (s != NULL) {
        s++; // Point to the first number
        while (*s) {
            thrust[i++] = *s++;
        }
        return atoi((char*)thrust);
    }
    return 0;
}
