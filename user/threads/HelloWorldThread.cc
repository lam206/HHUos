/*****************************************************************************
 *                                                                           *
 *                   H E L L O W O R L D T H R E A D                         *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Ein einfacher Thread.                                    *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 21.8.2016                       *
 *****************************************************************************/

#include "kernel/Globals.h"
#include "user/threads/HelloWorldThread.h"



/*****************************************************************************
 * Methode:         HelloWorldThread::run                                    *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einstiegsfunktion in unseren Thread.                     *
 *****************************************************************************/
void HelloWorldThread::run () {
    
    kout << "Hallo Welt von einem Thread!" << endl;
    
    // selbst terminieren
    scheduler.exit ();
}
