/*****************************************************************************
 *                                                                           *
 *                                M A I N                                    *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Startroutine, wird direkt vom Bootlader angesprungen,    *
 *                  nachdem dieser in den Protected Mode geschaltet hat und  *
 *                  die GDT und IDT initalisiert hat.                        *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 11.11.2016                      *
 *****************************************************************************/

#include "kernel/Globals.h"
#include "kernel/Allocator.h"
#include "user/HeapDemo.h"


int main() {
   
    // Speicherverwaltung initialisieren
    allocator.init();

    // Bildschirm loeschen.
    kout.clear();
    
    // Startmeldung ausgeben

    heap_demo();

    while (1);
    return 0;
 }
