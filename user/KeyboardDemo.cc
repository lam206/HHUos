/*****************************************************************************
 *                                                                           *
 *                        K E Y B O A R D D E M O                            *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Testausgaben für den CGA-Treiber.                        *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 26.10.2018                      *
 *****************************************************************************/

#include "kernel/Globals.h"
#include "user/KeyboardDemo.h"


void keyboard_demo() {

    /* Hier muess Code eingefuegt werden */
	kout << endl << "Tastatur mit Eingaben bitte testen" << endl;

    while (true) {
        Key key;

        if ((key = kb.key_hit()).valid()) {
            kout << (char)key.ascii() << endl;
        }
    }


}
