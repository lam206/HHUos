/*****************************************************************************
 *                                                                           *
 *                            H E A P D E M O                                *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Demonstration der dynamischen Speicherverwaltung.        *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 27.12.2016                      *
 *****************************************************************************/

#include "kernel/Globals.h"
#include "kernel/Allocator.h"
#include "user/heap/HeapDemo.h"
#include "user/heap/MyObj.h"


// Hilfsfunktion: Auf Return-Taste warten
void waitForReturn() {

    /* hier muss Code eingefuegt werden */

}


void heap_demo() {

	MyObj* obj = new MyObj(1);
	obj->tell_me_your_number();

	delete obj;

	obj->tell_me_your_number(); // use-after-free

	MyObj* obj2 = new MyObj(6);  // should be allocated to the same space where `datum` was before

	obj->tell_me_your_number();  // second use-after-free. Should print obj2's number if obj's memory was reused properly



	int *arr = new int[5];
	for (int i = 0; i < 5; i++) {
		arr[i] = i;
	}

	for (int i = 0; i < 5; i++) {
		kout << arr[i] << endl;
	}

	delete arr;
}
