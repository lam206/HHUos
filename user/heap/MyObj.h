#include "lib/util.h"
#include "kernel/Globals.h"

class MyObj {
	private:
		int mDay;
		int mMonth;
		int mYear;

	public:
		MyObj(int day, int month, int year) {
			mDay = day;
			mMonth = month;
			mYear = year;
		}

		void tell_me_the_date() {
			// char * example = "I'm the 8th of February 2020";

			char* str1 = "I'm the ";
			char* str2 = "th of ";
			char* str3 = " ";

			char* message = str2cat(str1, 
					str2cat(str(mDay),
					str2cat(str2,
					str2cat(str(mMonth),
					str2cat(str3, str(mYear))))));

			kout << message << endl;

		}



};
