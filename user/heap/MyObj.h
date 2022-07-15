#include "lib/util.h"
#include "kernel/Globals.h"

class MyObj {
	private:
		int number;

	public:
		MyObj(int num) {
			number = num;
		}

		void tell_me_your_number() {

			kout << number << endl;

		}

};
