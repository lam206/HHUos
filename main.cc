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
	pg_notpresent_page(page);
	*page = 10;  // schreibzugriff der bluescreen ausloesen sollte (page fault)

    
    // Anwendungscode aufrufen
   for (int i = 0;i >=0; i++) {
	   kout << "yep" ;
   }
    return 0;
 }
