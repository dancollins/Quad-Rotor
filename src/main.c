/**
 * @author: Dan
 * @since November 24, 2012, 3:03 PM
 * @version 1.0
 *
 * DESC
 */

#include <xc.h>

#include <math.h>

/* FreeRTOS */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "board.h"
#include "serial.h"

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
    xTaskCreate(serial_update, "Serial Transmission", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL);
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

    const WORD frequency = 400; // 400Hz
    const float dt = 1 / (float)frequency;

    const float timeConstant = 0.1;

    GyroData_t gyro;
    AccelData_t accel;
    BYTE buf[100];

    float accel_xAngle, accel_yAngle;
    float gyro_xRate, gyro_yRate, gyro_zRate;
    float gyro_xAngle, gyro_yAngle, gyro_zAngle;

    float filter_x[3];
    float filter_y[3];

    float complementary_x = 0, complementary_y = 0;

    while (TRUE) {
        accel_read(&accel);
        gyro_read(&gyro);

        accel_xAngle = 57.295*atan((float)accel.y/ sqrt(pow((float)accel.z,2)+pow((float)accel.x,2)));
	accel_yAngle = 57.295*atan((float)-accel.x/ sqrt(pow((float)accel.z,2)+pow((float)accel.y,2)));

        gyro_xRate = (float)gyro.x / 14.375;
        gyro_yRate = (float)gyro.y / 14.375;
        gyro_zRate = (float)gyro.z / 14.375;

        gyro_xAngle = gyro_xRate * dt;
        gyro_yAngle = gyro_yRate * dt;
        gyro_zAngle = gyro_zRate * dt;

        /* Second Order Complimetary Filter */
        /* https://github.com/big5824/Quadrocopter/blob/master/filters.c */
        filter_x[0] = (accel_xAngle - complementary_x) * timeConstant * timeConstant;
	filter_y[0] = (accel_yAngle - complementary_y) * timeConstant * timeConstant;
  	filter_x[2] = (dt * filter_x[0]) + filter_x[2];
  	filter_y[2] = (dt * filter_y[0]) + filter_y[2];
  	filter_x[1] = filter_x[2] + (accel_xAngle - complementary_x) * 2 * timeConstant + gyro_xRate;
  	filter_y[1] = filter_y[2] + (accel_yAngle - complementary_y) * 2 * timeConstant + gyro_yRate;

  	complementary_x = (dt * filter_x[1]) + complementary_x;
  	complementary_y = (dt * filter_y[1]) + complementary_y;

        sprintf(buf, "%1.3f,%1.3f\r\n", complementary_x, complementary_y);
        serial_putString(UART1, buf);

        vTaskDelayUntil(&time, dt * 1000);
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
