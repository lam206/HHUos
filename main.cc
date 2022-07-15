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
#include "user/TextMenu.h"


int main() {
    // Bildschirm loeschen.
    kout.clear ();

    // Speicherverwaltung initialisieren
    allocator.init();
    
    // Startmeldung ausgeben
    kout << "HHUos" << endl << "=========" << endl << endl;

    // Interrupts erlauben
    cpu.enable_int();

    // PIT in PIC einstoepseln
    pit.plugin();

    menu();
    
    // Anwendungscode aufrufen
	while (1) {

	}

    return 0;
 }
