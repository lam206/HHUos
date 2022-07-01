#include "user/preemptive/Counter.h"
#include "kernel/Globals.h"

void Counter::run() {
	int i = 0;
	while (1) {
		kout.setpos(20,20);
		kout << i << endl;
		i++;
	}
}

