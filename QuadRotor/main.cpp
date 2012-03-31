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


