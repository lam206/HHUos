#include "kernel/threads/Thread.h"

class Counter : public Thread {
	private:
		int pos;
	public:
		Counter(int inpos) : Thread() {
			this->pos = inpos;
		};

		void run();

};

