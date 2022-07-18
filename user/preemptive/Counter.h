#include "kernel/threads/Thread.h"
#include "kernel/Globals.h"
#include "lib/Semaphore.h"

class Counter : public Thread {

	private:
		int pos;
		Semaphore *sem;

	public:
		Counter (int inpos) : Thread() {
			this->pos = inpos;
		}

		Counter(int inpos, Semaphore *s) : Thread() {
			this->pos = inpos;
			this->sem = s;
		};

		void run();

};

