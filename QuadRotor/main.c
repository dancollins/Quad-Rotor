/*
	Quad Rotor Flight Controller
	file: main.c
	author: Dan Collins
	
	Interfaces with a number of sensors:
		+ 3 axis accelerometer
		+ 3 axis gyroscope
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

#include "motor.h" // Motor driver
#include "debug.h" // Debug serial driver
#include "radio.h" // Handles radio communication
#include "i2cdriver.h" // Handles initialisation stuff for I2C
#include "accel.h" // Accelerometer driver
#include "gyro.h" // Gyroscope driver
#include "imu.h" // IMU processor

#include <math.h> // Trig functions
#include <string.h> // Radio parsing

unsigned int thrust = 0;

int16_t saturate (int16_t var, int absmax) {
	if(var > absmax) {
		var = absmax;
	} else if(var < -absmax) {
		var = -absmax;
	}
	return var;
}

/*
	Blinky LED Thread
*/
static WORKING_AREA(waLEDThread, 128); // Working area for the thread

static msg_t LEDThread(void *arg) { // Blinky LED thread
	
	(void)arg; // Don't need arguments...
	
	systime_t time = chTimeNow(); // Get current time
	
	while (1) {
		time += MS2ST(50);
		palClearPad(IOPORT2, GPIOB_LED1); // Turn LED on
		chThdSleepUntil(time);
		time += MS2ST(950);
		palSetPad(IOPORT2, GPIOB_LED1); // Turn LED off
		chThdSleepUntil(time);
	}
	return 0;
}

/*
	Radio Thread
*/
static WORKING_AREA(waRadioThread, 128); // Working area for the thread

static msg_t RadioThread(void *arg) { // Radio thread
	
	(void)arg; // Don't need arguments...
	
	unsigned char radio_buffer[10] = {0};
	unsigned int old_thrust = 0;
	char *data_string; // Holds the incoming data string
	unsigned char in_checksum = 0; // holds the incoming checksum
	unsigned char checksum = 0; // The checksum calculated on the fly (that's a pun!)
	unsigned char i = 0; // loop index
	
	while (1) {
		uartStartReceive(&UARTD3, 10, radio_buffer); // Get radio data from UART
		chThdSleepMilliseconds(10);
		
		old_thrust = thrust; // Store old value to revert to if new data is bad

		data_string = strstr(radio_buffer, "t"); // Find first occurance of 't' TODO: Expand for larger datasets

		if (data_string != NULL) {
			data_string++; // Move to first character
			thrust = *data_string++; // Store first character into thrust
			in_checksum = *data_string++; // Next byte is the checksum

			if (thrust < 500) // Limit the value to this range
				thrust = 500;
			if (thrust > 900)
				thrust = 900;
			
			checksum = 't' ^ (char)thrust; // The 't' value received correctly because it passed the strstr check
		
			if (checksum != in_checksum) {
				debug_print("Radio: Error: Bad Checksum: ");
				debug_printn(in_checksum);
				debug_print(" Expected: ");
				debug_printn(checksum);
				debug_println(".");

				debug_println(radio_buffer); // Print the incoming string

				thrust = old_thrust; // bad checksum, so discard new data
			}
		}
			
		for (i=0; i<10; i++) {
			radio_buffer[i] = 0; // Clear buffer
		}
	}
	
	return 0;
}

/*
	I2C Thread
*/
static WORKING_AREA(waControllerThread, 1024); // Working area for the thread

static msg_t ControllerThread(void *arg) { // Controller thread
	(void)arg; // Don't need arguments...
	
	systime_t time = chTimeNow();
	
	int32_t pitch_angle_accum = 0;
	int32_t roll_angle_accum = 0;
	
	while (1) {
		accel_read();
		gyro_read();
		
		IMUupdate(gyro.x * 0.0012141420883438813, gyro.y * 0.0012141420883438813, gyro.z * 0.0012141420883438813, accel.x, accel.y, accel.z);
		
		float norm_x = 2*(q0*q2 - q1*q3);
		float norm_y = 2*(q0*q1 + q2*q3);
		float norm_z = (1 - 2*(q1*q1 + q2*q2));
		
		float elev = acosf(norm_z);
		float azim = atan2f(norm_y, norm_x);

		int16_t pitch = elev * sinf(azim) / M_PI * 32767;
		int16_t roll = elev * cosf(azim) / M_PI * 32767;
		int16_t yaw = 0;
		
		int16_t pitch_angle_target = 0; // TODO: Fix
		int16_t roll_angle_target = 0; // TODO: Fix

		int16_t pitch_angle_error = pitch_angle_target - pitch;
		int16_t roll_angle_error = roll_angle_target - roll;

		// 25 deg max error.
		pitch_angle_error = saturate(pitch_angle_error, 4551);
		roll_angle_error = saturate(roll_angle_error, 4551);

		pitch_angle_accum += pitch_angle_error;
		roll_angle_accum += roll_angle_error;
		
		// 20 deg s max error.
		pitch_angle_accum = saturate(pitch_angle_accum, 364088);
		roll_angle_accum = saturate(roll_angle_accum, 364088);

		int32_t pitch_rate_target = (pitch_angle_error * 2 * 65536 + pitch_angle_accum * 98) >> 16;
		int32_t roll_rate_target = (roll_angle_error * 2 * 65536 + roll_angle_accum * 98) >> 16;

		int16_t pitch_rate_comp = ((pitch_rate_target - (gyro.x * 4000 / 360)) * 6 * 36) >> 16;
		int16_t roll_rate_comp = ((roll_rate_target - (gyro.y * 4000 / 360)) * 6 * 36) >> 16;

		pitch_rate_comp = saturate(pitch_rate_comp, 250);
		roll_rate_comp = saturate(roll_rate_comp, 250);

		motor_set(0, pitch_rate_comp, roll_rate_comp, 0);
		
		time += MS2ST(100);
		chThdSleepUntil(time);
	}
	return 0;
}

/*
	BaseChannels
*/
BaseChannel *console; // Console Channel
BaseChannel *radio; // Radio Channel

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
	
	// Start Serial Console
	sdStart(&SD1, NULL);
	console = &SD1; // Use SerialDriver1 as console output
	debug_println("Init: Serial Driver Active");
	
	// Start Motors
	motor_init();
	debug_println("Init: Motor Driver Active");
	
	// Start Radio Comms
	radio_init();
	debug_println("Init: Radio Driver Active");
	
	// Start the I2C Module
	i2cdriver_init();
	
	// Create Threads
	chThdCreateStatic(waLEDThread, sizeof(waLEDThread), NORMALPRIO, LEDThread, NULL); // Create blinky LED thread
	chThdCreateStatic(waRadioThread, sizeof(waRadioThread), NORMALPRIO, RadioThread, NULL); // Create thread for reading radio data
	//chThdCreateStatic(waControllerThread, sizeof(waControllerThread), NORMALPRIO, ControllerThread, NULL); // Create thread for processing IMU

	// This is where the main thread actually starts...
	while (1) {
		chThdSleepMilliseconds(10);
		motor_set(thrust*10, 0, 0, 0);
	}
	return(0);
}
