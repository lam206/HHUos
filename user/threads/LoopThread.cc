/*****************************************************************************
 *                                                                           *
 *                        L O O P T H R E A D                                *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Demo eines Threads. Schleife die Zahlen ausgibt.         *
 *****************************************************************************/

#include "user/threads/LoopThread.h"
#include "kernel/Globals.h"


/*****************************************************************************
 * Methode:         LoopThread::run                                          *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Code des Threads.                                        *
 *****************************************************************************/
void LoopThread::run () {
   
   /* Hier muss Code eingefuegt werden */

	int counter = 0;
	while (1) {
		kout.setpos(10+20*id, 10);
		kout << "Thread" << id << ": " << counter;
		kout.flush();
		counter++;
		scheduler.yield();
	}

   
}
