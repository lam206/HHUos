/*****************************************************************************
 *                                                                           *
 *             C O O P E R A T I V E T H R E A D D E M O                     *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Beispiel für kooperative Threads.                        *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 21.8.2016                       *
 *****************************************************************************/

#include "kernel/Globals.h"
#include "user/CoopThreadDemo.h"
#include "user/LoopThread.h"


/*****************************************************************************
 * Methode:         CoopThreadDemo::run                                      *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Der Anwendungsthread erzeugt drei Threads die Zaehler    *
 *                  ausgeben und terminiert sich selbst.                     *
 *****************************************************************************/
void CoopThreadDemo::run () {
  
    /* Hier muss Code eingefuegt werden */
	LoopThread t0(0);
	LoopThread t1(1);
	LoopThread t2(2);

	scheduler.ready(&t0);
	scheduler.ready(&t1);
	scheduler.ready(&t2);

	for (int i = 0; i <= 1000; i++) {
		scheduler.yield();
	}

	scheduler.kill(&t1);
	scheduler.exit();
    
}
