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
#include "kernel/Paging.h"

extern "C" {
	void invalidate_tlb_entry(unsigned int*);
}

int main() {
    // Bildschirm loeschen.
    kout.clear ();
    
    // Startmeldung ausgeben
    kout << "HHUos" << endl << "=========" << endl << endl;
    // Tastatur-Unterbrechungsroutine einstoepseln
    kb.plugin ();
    pit.plugin ();
    
    // Interrupts erlauben (Tastatur)
    cpu.enable_int ();
    
    // Anwendungscode aufrufen
	while (1) {

	}

    return 0;
 }
