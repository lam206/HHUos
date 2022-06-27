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
#include "user/VBEdemo.h"
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
    
    // Interrupts erlauben (Tastatur)
    cpu.enable_int ();

    pg_init();

    unsigned int *page = pg_alloc_page();
    	*page = 0;
	pg_write_protect_page(page);

	invalidate_tlb_entry(page);  // removes the virtual adress from TLB virtual -> physical mapping.

	*page = 1;  // sollte nicht mehr klappen nach invlpg Befehl.

    
    // Anwendungscode aufrufen
   for (int i = 0;i >=0; i++) {
	   kout << "yep" ;
   }
    return 0;
 }
