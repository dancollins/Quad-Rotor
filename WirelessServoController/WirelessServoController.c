/*
 * Wireless Servo Controller
 * Dan Collins 2011
 *
 * Description:
 * Receives input from a serial port (made wireless by transparent
 * radio units) to control a servo connected to RC3.  Data can be
 * transmitted by a computer running a utility to read the state 
 * of an axis on the Xbox 360 Controller connected to windows.
 *
 * Hardware:
 * PIC: 18F87J11 - PICDEM PIC 18 Explorer
 * Servo: Standard Hobby Servo on RC3
 * UART: Using UART1 with the HopeRF HM-TR-TTL modules
 * Buzzer: Simple audable output on RD5 (self oscillating)
 *
 * This source code is realeased under the POPL Licence.
 * See LICENCE.TXT for details.
 *
 */
 
#include <p18cxxx.h>
#include <delays.h>

#pragma config WDTEN = OFF
#pragma config XINST = OFF
#pragma config CP0 = OFF
#pragma config FOSC = HS

#define xtal_freq 10000000ul

/* Prototypes */
void isr(void);
unsigned char find_start(void);

/* Global Variables */
/* Servo */
unsigned int s_ctr = 0; // Used to create a 20mS loop
unsigned int s_val = 0; // Sets the pulse width for servo position
unsigned int s_nval = 0; // Value for new servo position
/* UART */
unsigned char data[32] = {0}; // Serial ring buffer
unsigned char index = 0; // Buffer index
unsigned char flag = 0; // Serial complete flag

void delay_ms(int ms){
	unsigned int i=0;
	unsigned int j=0;
	for(i=0; i<ms; i++){
		for(j=0; j<(xtal_freq/120000); j++){
			Delay1TCY();
		}
	}
}

#pragma code high_vector=0x08
void high_interrupt(void) {
	_asm GOTO isr _endasm
}
#pragma code

#pragma interrupt isr
void isr(void) {
	/* Servo */
	if ((PIE1bits.TMR2IE) && (PIR1bits.TMR2IF)) {
		if (s_ctr < 1000) { // Still in the 20mS period
			if (s_ctr < s_val) { // Still waiting for the pulse to send
				LATCbits.LATC3 = 1; // Make sure the servo pin is high
			} else {
				LATCbits.LATC3 = 0; // Period is over, pull the pin low
			}
			s_ctr++;
		} else {
			s_ctr = 0; // Period is over
		}
		TMR2 = 205; // Load for 20uS operation
		PIR1bits.TMR2IF = 0; // Clear flag
	}
	/* Radio */
	if ((PIR1bits.RC1IF)&&(PIE1bits.RC1IE)) {
		data[index] = RCREG1;
		if (data[index] == 10) { // End of string
			flag = 1;
		}
		index++;
	}
}

void init(void) {
	/* Ports */
	TRISCbits.TRISC3 = 0; // Servo pin is output
	WDTCONbits.ADSHR = 1; // Some registers are shared, see Register 5-3
	ANCON0 = 0xFF; // Set Analog Pins
	ANCON1 = 0xFF; // Set Analog Pins
	WDTCONbits.ADSHR = 0;
	
	/* Timer 2 */
	T2CONbits.TMR2ON = 1; // Enable timer with 10MHz clock
	TMR2 = 205; // Load for 20uS operation
	
	/* UART 1 */
	TXSTA1 = 0x20;
	RCSTA1 = 0x90;
	SPBRG1 = 15;
	
	/* Interrupts */
	/* Clear Flags */
	PIR1bits.TMR2IF = 0;
	PIE1bits.RC1IE = 1;
	/* Peripheral Interrupts */
	PIE1bits.TMR2IE = 1; // Timer 2
	PIE1bits.RC1IE = 1; // UART 1
	/* Global Settings */
	INTCONbits.GIE = 1; // Enable all unmasked interrupts
	INTCONbits.PEIE = 1; // Enable peripheral interrupts
}

void main(void) {
	char start = 0; // Holds the posistion of the '@' character
	init(); // It's bad to forget to run this...
	s_val = 75; // Center the servo
	while(1) {
		while (!flag);
		start = find_start();
		flag = 0;
		index = 0;
		if (start != 255) {
			s_val = data[start+1];
		}
		/*if (s_val > s_nval) {
			while (s_val > s_nval) {
				s_val--;
				delay_ms(1);
			}
		} else if (s_val < s_nval) {
			while (s_val < s_nval) {
				s_val++;
				delay_ms(1);
			}
		}*/
	}
}

unsigned char find_start(void) {
	char i;
	for (i=0; i<32; i++) {
		if (data[i] == '@') {
			return i;
		}
	}
	return 255;
}
