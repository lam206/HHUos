#include "user/preemptive/Counter.h"
#include "kernel/Globals.h"

void Counter::run() {
	int i = 0;
	while (1) {
		kout.setpos(10,this->pos);
		kout << i << endl;
		i++;
	}
}

