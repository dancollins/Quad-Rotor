#ifndef TIME_H
#define TIME_H

#include "thread.h"

class Time {
	private:
		static volatile uint32_t systime;
	
	public:
		inline static void tick() {
			systime++;
		}
		
		inline static void sleep(uint32_t ms) {
			ms += systime;
			while(systime < ms) {
				Thread::yield();
			}
		}
};

#endif
