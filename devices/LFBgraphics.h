/*****************************************************************************
 *                                                                           *
 *                            L F B G R A P H I C S                          *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Zeichenfunktionen fuer Grafikmodi, die auf einem         *
 *                  linearen Framebuffer basieren. Verwendet in VESA und     *
 *                  QemuVGA.                                                 *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 19.9.2016                       *
 *                  Der Code fuer das Zeichnen der Linie ist von Alan Wolfe  *
 *         https://blog.demofox.org/2015/01/17/bresenhams-drawing-algorithms *
 *****************************************************************************/

#ifndef __LFBgraphics_include__
#define __LFBgraphics_include__

#include "devices/fonts/Fonts.h"


// Hilfsfunktionen um Farbwerte fuer einen Pixel zu erzeugen
#define RGB_24(r,g,b) (unsigned int) ((r << 16) + (g << 8) + b )

#define BUFFER_INVISIBLE 0
#define BUFFER_VISIBLE   1

class LFBgraphics {
    
private:
    LFBgraphics (const LFBgraphics &copy);  // Verhindere Kopieren

    // Hilfsfunktion fuer drawString
    void drawMonoBitmap   ( unsigned int x, unsigned int y, 
                            unsigned int width, unsigned int height, 
                            unsigned char* bitmap, unsigned int col);

	unsigned int sqrt(unsigned int x) ;

public:

    unsigned int xres, yres;        // Aufloesung in Pixel
    unsigned int bpp;               // Farbtiefe (Bits per Pixel)
    unsigned int lfb;               // Adresse des Linearen Framebuffers
    unsigned int hfb;				// Adresse des versteckten Buffers (optional, fuer Animationen)
    unsigned int mode; 				// Zeichnen im sichtbaren = 1 oder unsichtbaren = 0 Puffer 
    
    LFBgraphics () { mode = BUFFER_VISIBLE; };
    
    unsigned int palette(unsigned char r, unsigned char g, unsigned char b);

    void clear            ();
    void drawPixel        ( unsigned int x, unsigned int y, unsigned int col);
    
    void drawString       (Font &fnt, unsigned int x, unsigned int y,  
                            unsigned int col, char* str, unsigned int len);
    
	void drawSprite(unsigned int sprite_height, unsigned int sprite_width, unsigned int sprite_bpp, unsigned char *sprite_pixel, unsigned int xstart, unsigned int ystart);

	void drawRectangle(unsigned int xstart, unsigned int ystart, unsigned int height, unsigned int width, unsigned int col);
	void drawCircle(int xCenter, int yCenter, int radius, unsigned int c);

    // stellt ein, ob in den sichtbaren Puffer gezeichnet wird
    void setDrawingBuff( int v);
    
    // kopiert 'hfb' nach 'lfb'
    void copyHiddenToVisible();
    
};

#endif
