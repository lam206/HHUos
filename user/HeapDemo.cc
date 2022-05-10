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
#include "user/HeapDemo.h"
#include "user/MyObj.h"


// Hilfsfunktion: Auf Return-Taste warten
void waitForReturn() {

    /* hier muss Code eingefuegt werden */

}


void heap_demo() {

   /* hier muss Code eingefuegt werden */
	MyObj* datum = new MyObj(1, 1, 2000);
	datum->tell_me_the_date();

	/* arrays not working
	int arr[] = new int[9];
	for (int i = 0; i < 10; i++) {
		arr[i] = i;
	}

	kout.print(arr-10, 1000, kout.STD_ATTR);
	*/


}
