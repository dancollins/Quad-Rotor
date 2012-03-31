#include "gps.h"

GPS* GPS::self;

template<>
void interrupt<Interrupt::USART3>() {
	GPS::self->irq();
}

void GPS::irq() {
	
	uint8_t c = USART3.DR;
	
	if(!incomplete_msg) {
		incomplete_msg = msg_pool.create();
		
		if(!incomplete_msg) {
			return;
		}
	}
	
	if(incomplete_msg->n == 0 && c != '$') {
		return;
	}
	
	if(incomplete_msg->n >= 128) {
		incomplete_msg->n = 0;
		return;
	}
	
	incomplete_msg->buf[incomplete_msg->n++] = c;
	
	if(c == '\n') {
		GPIOB.ODR ^= 1 << 1;
		
		const_cast<P<GPSMsg>&>(complete_msg) = incomplete_msg;
		incomplete_msg.reset();
		complete = true;
	}
}
