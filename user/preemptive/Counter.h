#include "kernel/threads/Thread.h"

class Counter : public Thread {
	private:
	public:
		Counter() : Thread() {};

		void run();

};

