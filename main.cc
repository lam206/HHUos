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
#include "user/preemptive/Counter.h"
#include "user/preemptive/Player.h"

extern "C" {
	void invalidate_tlb_entry(unsigned int*);
}

int main() {
    // Bildschirm loeschen.
    kout.clear ();
    allocator.init();
    
    // Startmeldung ausgeben
    kout << hex << 16 << endl;
    kout << "HHUos" << endl << "=========" << endl << endl;
    // Tastatur-Unterbrechungsroutine einstoepseln
    kb.plugin ();
    pit.plugin ();
    
    // Interrupts erlauben (Tastatur)
    cpu.enable_int ();

    Semaphore s(1);

    Counter counter(0, &s);
    Counter counter2(10, &s);
    Counter counter3(20, &s);
    Player player;
    IdleThread idle;

    scheduler.ready(&idle);
    scheduler.ready(&counter);
    scheduler.ready(&counter2);
    scheduler.ready(&counter3);
    scheduler.ready(&player);
    scheduler.schedule();
    
    // Anwendungscode aufrufen
	while (1) {

	}

    return 0;
 }
