/*****************************************************************************
 *                                                                           *
 *                       C O R O U T I N E L O O P                           *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Loop ist eine Koroutine, die nichts weiter tut als einen *
 *                  Zaehler hochzuzaehlen und diesen auf dem Bildschirm      *
 *                  anzuzeigen und dann auf die naechste Korotuine umzu-     *
 *                  schalten.				 	 	 	           			 *
 *                                                                           *
 * Autor:           Olaf Spinczyk, TU Dortmund                               *
 *****************************************************************************/

#include "user/threads/ThreadLoop.h"
#include "kernel/Globals.h"


/*****************************************************************************
 * Methode:         ThreadLoop::run                                       *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einstiegsfunktion der Koroutine.                         *
 *****************************************************************************/
void ThreadLoop::run () {

   /* Hier muss Code eingefuegt werden */
	int counter = 0;
	while (1) {
		kout.setpos(10+20*this->tid, 10);
		kout << "Thread " << this->tid << ": " << counter;
		kout.flush();
		counter++;
		scheduler.yield();
	}

}
