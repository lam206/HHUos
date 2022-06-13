/*****************************************************************************
 *                                                                           *
 *                                M A I N                                    *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Startroutine, wird direkt vom Bootlader angesprungen,    *
 *                  nachdem dieser in den Protected Mode geschaltet hat und  *
 *                  die GDT und IDT initalisiert hat.                        *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 15.8.2016                       *
 *****************************************************************************/

#include "kernel/Globals.h"
#include "kernel/threads/IdleThread.h"


int main() {
    // Bildschirm loeschen.
    kout.clear ();
    
    // Startmeldung ausgeben
    kout << "HHUos 0.4" << endl << "=========" << endl << endl;
    
    // Tastatur-Unterbrechungsroutine einstoepseln
    kb.plugin ();
    
    // Interrupts erlauben (Tastatur)
    cpu.enable_int ();
    
    // Anwendungscode aufrufen
	IdleThread idle;
	scheduler.ready(&idle);
	kout << "original thread pointer: " << &idle << endl;
	scheduler.schedule();

    
    return 0;
 }
