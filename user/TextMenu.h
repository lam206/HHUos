#include "kernel/Globals.h"
#include "user/text/TextDemo.h"
#include "user/sound/SoundDemo.h"
#include "user/keyboard/KeyboardDemo.h"
#include "user/heap/HeapDemo.h"
#include "user/keyboard/KeyIRQDemo.h"
#include "user/preemptive/PreemptiveMultitaskingDemo.h"

void menu() {
	kout << "1. Textausgabe" << endl;
	kout << "2. Sound" << endl;
	kout << "3. Tastatur (polling)" << endl;
	kout << "4. Heap" << endl;
	kout << "5. Tastatur (via interrupt)" << endl;
	kout << "6. Preemptive multitasking" << endl;

	Keyboard k;
	Key key = k.key_hit();
	switch (key.ascii()) {
		case '1':
			text_demo();
			break;
		case '2':
			sound_demo();
			break;
		case '3':
			keyboard_demo();
			break;
		case '4':
			heap_demo();
			break;
		case '5':
			key_irq_demo();
			break;
		case '6':
			preemptive_multitasking_demo();
			break;

	}

}





