/*
	Quad Rotor Flight Controller
	file: blinky_led.c
	author: Dan Collins
			
	Blinks an LED on the board to make sure everything works!
*/

#include "ch.h"
#include "hal.h"

/*
 * Blinky LED Thread
 */
static WORKING_AREA(waBlinky, 128); // Static working area for the thread

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
 * Application entry point.
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

	chThdCreateStatic(waBlinky, sizeof(waBlinky), NORMALPRIO, Blinky, NULL); // Create blinky LED thread

	// This is where the main thread actually starts...
	while (1) {
		chThdSleepMilliseconds(500); // Waste time!  The 'main' thread in this case is the blinky LED
	}
	return(0);
}
