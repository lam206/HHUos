#include "lib/Semaphore.h"
#include "kernel/Globals.h"

void Semaphore::p() {
	lock.acquire();
	if (this->counter > 0) {
		counter -= 1;
		lock.release();
	} else {
		this->waitQueue.enqueue(scheduler.get_active());
		lock.release();
		scheduler.block();
	}
}

void Semaphore::v() {
	lock.acquire();
	char isEmpty = this->waitQueue.is_empty();
	if (isEmpty) {
		this->counter += 1;
	} else {
		Thread* waiting = (Thread*)this->waitQueue.dequeue();
		scheduler.deblock(*waiting);
	}
	lock.release();
}
