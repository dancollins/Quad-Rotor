/*
 * WJoystickServoController
 * Dan Collins 2011
 *
 * Description:
 * Reads the value on the Xbox 360 Controller using the SDL library.  The value is converted
 * to a smaller linear range (changed from "-32767 to 32767" to "20 to 70".  This new value
 * is sent over the serial port.  It is also displayed in the terminal.
 *
 * This source code is realeased under the POPL Licence.
 * See LICENCE.TXT for details.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <SDL.h>
#include "serial.h"

int print_header(void);
int print_usage(char * appname);

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

void WatchJoystick(SDL_Joystick *joystick, int port) {
	int done = 0, value = 0, old_value = 0;
	SDL_Event event;
	char write_string[3] = "@1\n";
	while(!done) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_JOYAXISMOTION:
#ifdef DEBUGGING
				printf("Joystick %d axis %d value: %d\n", event.jaxis.which, event.jaxis.axis, event.jaxis.value);
#endif
				break;
			case SDL_JOYBUTTONDOWN:
#ifdef DEBUGGING
				printf("Joystick %d button %d down\n", event.jbutton.which, event.jbutton.button);
#endif
				break;
			case SDL_QUIT:
				done = 1;
				break;
			default:
				break;
			}
		}
		if (SDL_JoystickGetButton(joystick, 1) == SDL_PRESSED) { // B, Quit
			done = 1;
		}
		value = SDL_JoystickGetAxis(joystick, 3);
		if ((value > 500)||(value<-500)) {
			value = ((((value+32767)*50)/65535)+20);
			if (value != old_value) {
				old_value = value;
				write_string[1] = value;
				printf("%d\n", value);
				serial_write(port, write_string, 3);
			}
		}
	}
}

int main(int argc, char *argv[]) {
	SDL_Joystick *joystick;
	char *param_port=NULL;
	int port, ret, opt;

	fflush(stdout);
	print_header();

	if (argc <= 1) { // If there were no arguments
		print_usage(argv[0]);
		exit(-1);
	}

	while ((opt = getopt(argc, argv, "p:")) != -1) {
		switch (opt) {
		case('p'):
				param_port = strdup(optarg);
				break;
		}
	}

	port = serial_open(param_port);
	ret = serial_setup(port, (speed_t) 115200);
	if (ret == -1) {
		printf("Serial Setting Error!\n");
		exit(-1);
	}

	// Init SDL
	SDL_InitSubSystem(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK);

	if (SDL_NumJoysticks()>0) {
		SDL_JoystickEventState(SDL_ENABLE);
		joystick = SDL_JoystickOpen(0);
		if (joystick == NULL) {
			printf("Error");
		} else {
			WatchJoystick(joystick, port);
		}

		SDL_JoystickClose(joystick);
	}
	SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
	serial_close(port);

	return(0);
}

int print_header(void) {
	printf("\n");
	printf("--------------------------------------------------\n");
	printf("\n");
	printf(" Joystick Servo Control\n");
	printf(" Dan Collins 2011\n");
	printf(" Released under the Primis Open Programming License (POPL)\n");
	printf(" See LICENCE.TXT for details\n");
	printf("\n");
	printf("--------------------------------------------------\n");
	printf("\n");
	return 0;
}

int print_usage(char * appname) {
	printf(" Help Menu\n");
	printf(" Usage: %s -p COM3\n", appname);
	printf("\n");
	printf(" Options:\n");
	printf("          -p Number of serial port.\n");
	printf("\n");
	printf("--------------------------------------------------\n");
	return 0;
}

