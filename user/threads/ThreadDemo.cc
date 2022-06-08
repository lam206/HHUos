/*****************************************************************************
 *                                                                           *
 *                      C O R O U T I N E D E M O                            *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einstieg in eine Anwendung.                              *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 15.8.2016                       *
 *****************************************************************************/

#include "kernel/Globals.h"
#include "user/threads/ThreadDemo.h"
#include "user/threads/ThreadLoop.h"
#include "kernel/threads/IdleThread.h"


/*****************************************************************************
 * Methode:         ThreadDemo::main                                      *
 *---------------------------------------------------------------------------*
 * Beschreibung:    main-Methode der Anwendung.                              *
 *****************************************************************************/
void ThreadDemo::main () {

    /* 
     * Hier muss Code eingefuegt werden 
     */

	ThreadLoop app1;
	ThreadLoop app2;
	ThreadLoop app3;
	IdleThread idle;

	scheduler.ready(&idle);
	scheduler.ready(&app1);
	scheduler.ready(&app2);
	scheduler.ready(&app3);

	scheduler.schedule();

}
