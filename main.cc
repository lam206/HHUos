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
#include "user/KeyIRQDemo.h"
#include "user/SyncDemo.h"


int main() {
    
    // Speicherverwaltung initialisieren
    allocator.init();

    // Bildschirm loeschen.
    kout.clear();
    
    // Tastatur-Unterbrechungsroutine 'einstoepseln'
    /* hier muss Code eingefuegt werden */
	kb.plugin();
    
    // Interrupts erlauben (Tastatur)
    /* hier muss Code eingefuegt werden */
	cpu.enable_int();
  
    key_irq_demo();

  
    while (1) ; // wir kehren nicht zum Bootlader zurueck
    return 0;
 }
