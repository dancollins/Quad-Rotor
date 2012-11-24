/**
 * @author: Dan
 * @since November 24, 2012, 3:03 PM
 * @version 1.0
 *
 * DESC
 */

#include <xc.h>

/* FreeRTOS */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "board.h"

void blinkyLED(void * pvParameters); // Blinky LED thread

void init(void) {
    board_init(); // Prepare the low-level stuff
}

int main(void) {
    init();

    /* Create some threads */
    xTaskCreate(blinkyLED, "Blinky LED", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);

    vTaskStartScheduler(); // Start the scheduler

    return 0; // Program should never get here.
}

/**
 * Blinks an LED at 0.5Hz to show the system is working
 * @param pvParameters Parameters to be passed to this thread on creation.
 */
void blinkyLED(void * pvParameters) {
    portTickType time = xTaskGetTickCount();

    while (TRUE) {
        led1 ^= 1; // Toggle the LED
        vTaskDelayUntil(&time, 500); // Sleep for 500 ticks
    }
}

/**
 * Called when there is a stack overflow.  Not good.!
 */
void vApplicationStackOverflowHook(void) {
    // Turn on a bunch of LEDs!
    led1 = 1;
    led2 = 1;
    led3 = 1;
    led4 = 1;

    // Do nothing..!
    while(1);
}
