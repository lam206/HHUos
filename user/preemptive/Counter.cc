#include "user/preemptive/Counter.h"

void Counter::run() {
	int i = 0;
	while (1) {
		sem->p();
		kout.setpos(10,this->pos);
		kout << i << endl;
		sem->v();
		i++;
	}
}

