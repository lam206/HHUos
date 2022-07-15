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
#include "user/coroutines/CoroutineDemo.h"
#include "user/coroutines/CoroutineLoop.h"


// Stacks (koennen alternative auch per 'new' alloziert werden)
static unsigned int stack[3][1024];


/*****************************************************************************
 * Methode:         CoroutineDemo::main                                      *
 *---------------------------------------------------------------------------*
 * Beschreibung:    main-Methode der Anwendung.                              *
 *****************************************************************************/
void CoroutineDemo::main () {

    /* 
     * Hier muss Code eingefuegt werden 
     *
     * Die 3 Koroutinen einrichten, verketten und die 1. starten
     *
     */

	CoroutineLoop app1((unsigned int*)stack[0], 0);
	CoroutineLoop app2((unsigned int*)stack[1], 1);
	CoroutineLoop app3((unsigned int*)stack[2], 2);

	app1.setNext((Chain*)&app2);
	app2.setNext((Chain*)&app3);
	app3.setNext((Chain*)&app1);

	app1.start();

}
