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

#include "gyro.h"
#include "accel.h"

void blinkyLED(void * pvParameters); // Blinky LED thread
void testThread(void * pvParameters); // Used to test various modules as they are created

void init(void) {
    board_init(); // Prepare the low-level stuff
    serial_init(); // Prepare the serial port/s
    iic_init(); // Prepare the I2C module/s

    gyro_init(); // Prepare the gyroscope
    accel_init(); // Prepare the accelerometer
}

int main(void) {
    init();

    serial_putString(UART1, "Starting up...\r\n");

    /* Create some threads */
    xTaskCreate(blinkyLED, "Blinky LED", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+3, NULL);
    xTaskCreate(board_update, "Low Level Updater", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL);
    xTaskCreate(testThread, "Test Thread", 1000, NULL, tskIDLE_PRIORITY+2, NULL);

    vTaskStartScheduler(); // Start the scheduler

    return 0; // Program should never get here.
}

/**
 * Blinks an LED at 0.5Hz to show the system is working
 * @param pvParameters This thread doesn't take any parameters
 */
void blinkyLED(void * pvParameters) {
    portTickType time = xTaskGetTickCount();

    while (TRUE) {
        led1 ^= 1; // Toggle the LED
        vTaskDelayUntil(&time, 500); // Sleep for 500 ticks
    }
}

/**
 * Used to test modules as they are created
 * @param pvParameters This thread doesn't take any parameters
 */
void testThread(void * pvParameters) {
    portTickType time = xTaskGetTickCount();

    GyroData_t gyro;
    AccelData_t accel;
    BYTE buf[100];

    while (TRUE) {
        accel_read(&accel);
        gyro_read(&gyro);

        sprintf(buf, "%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%1.3f\r\n", accel.x, accel.y, accel.z, gyro.x, gyro.y, gyro.z);
        serial_putString(UART1, buf);

        vTaskDelayUntil(&time, 50);
    }
}

/**
 * Called (repeatedly) when the system is idling.
 * This hook is used to keep the system in a lower power state.
 */
void vApplicationIdleHook(void) {
    board_idle();
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
