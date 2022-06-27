/*****************************************************************************
 *                                                                           *
 *                             I D L E T H R E A D                           *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Wird nur aktiviert, wenn kein Thread arbeiten moechte.   *
 *                                                                           *
 * Autor:           Michael, Schoettner, HHU, 18.1.2019                      *
 *****************************************************************************/

#ifndef __IdleThread_include__
#define __IdleThread_include__


#include "kernel/threads/Thread.h"
#include "kernel/Globals.h"


class IdleThread : public Thread {
    
private:
    IdleThread(const Thread &copy); // Verhindere Kopieren

public:
    IdleThread () : Thread () {  }
    
    void run () {
        
        // Idle-Thread läuft, ab jetzt ist der Scheduler fertig initialisiert
        scheduler.setInitialized();
        
        while (1) {
            // CPU sofort abgeben, damit ein evt.
            // wartender Thread sofort loslegen kann.
            scheduler.yield ();
        }
    }
    
 };

#endif
