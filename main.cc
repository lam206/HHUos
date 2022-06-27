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
    	*page = 0;
	pg_write_protect_page(page);
	*page = 1;  // sollte klappen wegen TLB (das erste *page = 0 funktioniert und lagert dann die mapping im TLB ab. bei erneutem write wird dann gar nicht mehr der page table entry durchlaufen. es wird uebersehen, dass die page nun write protected ist).

    
    // Anwendungscode aufrufen
   for (int i = 0;i >=0; i++) {
	   kout << "yep" ;
   }
    return 0;
 }
