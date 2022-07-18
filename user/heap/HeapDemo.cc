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
	kout << endl;

	kout << "Press enter" << endl;

	Key k;
    /* hier muss Code eingefuegt werden */
	while( !((k = kb.key_hit()).valid()) || k.ascii() != '\n') {

	}

	kout.clear();

}


void heap_demo() {
	kout << hex;
	verbose = 1;

	kout.clear();
	kout << "Demo 1/4: 2 objekte dynamisch allozieren" << endl;
	allocator.dump_free_memory();
	kout << "objekte anlegen" << endl;
	MyObj* obj = new MyObj(1);
	MyObj* obj2 = new MyObj(6);
	allocator.dump_free_memory();
	waitForReturn();

	kout.clear();
	kout << "Demo 2/4: 2 objekte wieder freigeben" << endl;
	delete obj;
	delete obj2;
	allocator.dump_free_memory();
	waitForReturn();

	kout.clear();
	kout << "Demo 3/4: array mit drei objekten anlegen und inhalt eines objektes ausgeben" << endl;
	kout << "Array anlegen" << endl;
	MyObj* arr = new MyObj[3];
	for (int i = 0; i < 3; i++) {
		MyObj o = MyObj(i);
		arr[i] = o;
	}
	kout << "1. objekt im array" << endl;
	kout << "o[0]: number=" << arr[0].number << endl;
	allocator.dump_free_memory();
	waitForReturn();

	kout.clear();
	kout << "array wieder freigeben" << endl;
	kout << "Delete" << endl;
	delete arr;
	allocator.dump_free_memory();

	kout << "Ende" << endl;
}
