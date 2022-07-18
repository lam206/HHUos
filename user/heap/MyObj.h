#include "lib/util.h"
#include "kernel/Globals.h"

class MyObj {

	public:
		int number;

		MyObj() {
			number = 7;
		}

		MyObj(int num) {
			number = num;
		}

		void tell_me_your_number() {

			kout << number << endl;

		}

};
