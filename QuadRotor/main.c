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
		- BLDC motor via ESC
		* Transceiver over serial
			* Debugging information
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

#include "motor.h"

/*
	Blinky LED Thread
*/
static WORKING_AREA(waBlinky, 128); // Working area for the thread

static msg_t Blinky(void *arg) { // Blinky LED thread
	
	(void)arg; // Don't need arguments...
	
	while (1) {
		palClearPad(IOPORT2, GPIOB_LED1); // Turn LED on
		chThdSleepMilliseconds(500); // Wait 500ms
		palSetPad(IOPORT2, GPIOB_LED1); // Turn LED off
		chThdSleepMilliseconds(500); // Wait 500ms
	}
}

/*
 * Serial Output
 */
void serial_print(BaseChannel *chp, const char *msg) {
  while (*msg)
    chIOPut(chp, *msg++);
}

void serial_println(BaseChannel *chp, const char *msg) {
	serial_print(chp, msg);
	chIOPut(chp, '\n');
}

/*
	Application entry point.
*/
int main(void) {
	/*
	* System initializations.
	* - HAL initialization, this also initializes the configured device drivers
	*   and performs the board-specific initializations.
	* - Kernel initialization, the main() function becomes a thread and the
	*   RTOS is active.
	*/
	halInit();
	chSysInit();
	
	sdStart(&SD1, NULL);

	chThdCreateStatic(waBlinky, sizeof(waBlinky), NORMALPRIO, Blinky, NULL); // Create blinky LED thread

	// This is where the main thread actually starts...
	while (1) {
		serial_println((BaseChannel *)&SD1, "Hello, World!");
		chThdSleepMilliseconds(500); // Waste time!  The 'main' thread in this case is the blinky LED
	}
	return(0);
}
