#include "lib/Semaphore.h"
#include "kernel/Globals.h"

void Semaphore::p() {
	lock.acquire();
	if (this->counter > 0) {
		counter -= 1;
		lock.release();
	} else {
		lock.release();
		scheduler.block();
	}
}

void Semaphore::v() {
	lock.acquire();
	char isEmpty = this->waitQueue.is_empty();
	kout << "isEmpty: " << isEmpty << endl;
	if (isEmpty) {
		this->counter += 1;
	} else {
		kout << "getting something from waitQuee" <<endl;
		Thread* waiting = (Thread*)this->waitQueue.dequeue();
		scheduler.deblock(*waiting);
	}
	kout << "after if-else" << endl;
	lock.release();
}
