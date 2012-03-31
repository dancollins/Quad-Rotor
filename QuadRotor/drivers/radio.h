#ifndef RADIO_H
#define RADIO_H

#include <stdint.h>
#include "usart.h"
#include "mutex.h"

class Radio {
	public:
		Mutex radio_mutex;

		uint16_t values[4]; // Throttle, pitch, roll, yaw.

		void send(int len, const uint8_t* buf) {
			radio_mutex.lock();
	
			for(int i = 0; i < len; i++)
				usart_send(buf[i]);
	
			radio_mutex.unlock();
		}

		/*void receive(void) { // TODO!

		}*/
};

#endif
