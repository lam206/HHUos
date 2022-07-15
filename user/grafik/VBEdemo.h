/*****************************************************************************
 *                                                                           *
 *                             V B E D E M O                                 *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Demo zu VESA.                                            *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 26.12.2016                      *
 *****************************************************************************/
#ifndef __VBEdemo_include__
#define __VBEdemo_include__


#include "kernel/threads/Thread.h"


class VBEdemo : public Thread {
    
private:
    VBEdemo (const VBEdemo &copy); // Verhindere Kopieren

    // Hilfsfunktionen fuer drawColors()
    int linInterPol1D (int x, int xr, int l, int r);
    int linInterPol2D (int x, int y, int lt, int rt, int lb, int rb);

public:
    // Gib dem Anwendungsthread einen Stack.
    VBEdemo () : Thread () { }

    // Thread-Startmethode
    void run ();

    // Farbraum ausgeben
    void drawColors ();

    // Bitmap aus GIMP ausgeben
    void drawBitmap ();

    // Fonts ausgeben
    void drawFonts ();
};

#endif
