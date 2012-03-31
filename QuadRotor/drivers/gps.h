#ifndef GPS_H
#define GPS_H

#include "stm32.h"
#include "interrupt.h"
#include "thread.h"

#include "pool.h"

struct GPSMsg {
	unsigned int n;
	uint8_t buf[128];
	
	GPSMsg() : n(0) {}
};

class GPS {
	friend void interrupt<Interrupt::USART3>();
	
	private:
		static GPS* self;
		
		void irq();
		
		Pool<GPSMsg, 4> msg_pool;
		
		P<GPSMsg> incomplete_msg;
		volatile P<GPSMsg> complete_msg;
		
		volatile bool complete;
	
	public:
		GPS() {
			self = this;
		}
		
		void enable() {
			RCC.enable(RCC.USART3);
			USART3.BRR = 7500; // 4800 baud
			USART3.CR1 = 0x202c;
			
			Interrupt::enable(Interrupt::USART3);
		}
		
		P<GPSMsg> read() {
			while(!complete) {
				Thread::yield();
			}
			
			complete = false;
			
			P<GPSMsg> msg = const_cast<P<GPSMsg>&>(complete_msg);
			
			const_cast<P<GPSMsg>&>(complete_msg).reset();
			
			return msg;
		}
};

#endif
