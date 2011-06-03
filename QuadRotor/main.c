/*
	Quad Rotor Flight Controller
	file: main.c
	author: Dan Collins
	
	Interfaces with a number of sensors:
		- 3 axis accelerometer
		- 3 axis gyroscope
		- Motor speed
		- GPS
	
	And a number of inputs:
		- Transceiver over serial
			- Waypoints
			- Altitude
			- Attitude
		
	Processes the information in order to
	Run the outputs:
		+ BLDC motor via ESC
		* Transceiver over serial
			+ Debugging information
			- Current 'job'
			- Heading
			- Altitude
			- Attitude
			
	Note: The tasks have different states of completion as indicated by bullet points:
		- Not yet started
		* Work in progress
		+ Functioning
			
	The aim is to provide a flight controller for a quad rotor platform for use in surveying.
*/

#include "ch.h"
#include "hal.h"

#include "motor.h" // Motor Driver
#include "serial.h" // Serial Driver

/*
	Blinky LED Thread
*/
static WORKING_AREA(waBlinky, 128); // Working area for the thread

static msg_t Blinky(void *arg) { // Blinky LED thread
	
	(void)arg; // Don't need arguments...
	
	while (1) {
		palClearPad(IOPORT2, GPIOB_LED1); // Turn LED on
		chThdSleepMilliseconds(50);
		palSetPad(IOPORT2, GPIOB_LED1); // Turn LED off
		chThdSleepMilliseconds(950);
	}
}

BaseChannel *chp; // Console Channel

/*
	Application entry point.
*/
int main(void) {
	uint16_t thrust = 1000;
	/*
	* System initializations.
	* - HAL initialization, this also initializes the configured device drivers
	*   and performs the board-specific initializations.
	* - Kernel initialization, the main() function becomes a thread and the
	*   RTOS is active.
	*/
	halInit();
	chSysInit();
	
	// Start Serial Console
	sdStart(&SD1, NULL);
	chp = &SD1; // Use SerialDriver1 as serial output
	serial_println("Serial Active");
	
	// Start Motors
	motor_init();
	serial_println("Motors Active");
	
	// Create Threads
	chThdCreateStatic(waBlinky, sizeof(waBlinky), NORMALPRIO, Blinky, NULL); // Create blinky LED thread

	// This is where the main thread actually starts...
	while (1) {
		while (!palReadPad(IOPORT3, GPIOC_BUTTON2)) {
			for (thrust=500; thrust<1000; thrust+=10) {
				motor_set(thrust);
				serial_print("Thrust = ");
				serial_printn(thrust);
				serial_println("");
				chThdSleepMilliseconds(50);
			}
			chThdSleepMilliseconds(1000);
			for (thrust=1000; thrust>500; thrust-=10) {
				motor_set(thrust);
				serial_print("Thrust = ");
				serial_printn(thrust);
				serial_println("");
				chThdSleepMilliseconds(50);
			}
			chThdSleepMilliseconds(2000);
		}
	}
	return(0);
}
