#include "kernel/threads/Thread.h"

class Player : public Thread {
	private:
	public:
		Player() : Thread() {};

		void run();
};
