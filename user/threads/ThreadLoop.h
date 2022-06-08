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

#ifndef __coroutineloop_include__
#define __coroutineloop_include__

#include "kernel/threads/Thread.h"

class ThreadLoop : public Thread {
    
private:
    int id;

    ThreadLoop (const ThreadLoop &copy); // Verhindere Kopieren
    
public:
    // Gibt der Loop einen Stack und eine Id.
    ThreadLoop () {};

    // Zaehlt einen Zaehler hoch und gibt ihn auf dem Bildschirm aus.
    void run ();

    ~ThreadLoop ();
};

#endif
