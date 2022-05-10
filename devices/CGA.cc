/*****************************************************************************
 *                                    C G A                                  *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Mit Hilfe dieser Klasse kann man auf den Bildschirm des  *
 *                  PCs zugreifen. Der Zugriff erfolgt direkt auf der Hard-  *
 *                  wareebene, d.h. ueber den Bildschirmspeicher und den     *
 *                  I/O-Ports der Grafikkarte.                               *
 *                                                                           *
 * Autor:           Olaf Spinczyk, TU Dortmund                               *
 *                  Aenderungen von Michael Schoettner, HHU, 21.8.2016       *
 *****************************************************************************/
#include "devices/CGA.h"
#include "lib/util.h"

/*****************************************************************************
 * Methode:         CGA::setpos                                              *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Setzen des Cursors in Spalte x und Zeile y.              *
 *****************************************************************************/
void CGA::setpos (int x, int y) {

    /* Hier muess Code eingefuegt werden */
	if (x<0 || x>=COLUMNS || y<0 || y>=ROWS) {
		return;  // do nothing if out of bounds values used
	}

	unsigned short offset = COLUMNS * y + x;
	unsigned char offset_low = offset & 0xFF;
	unsigned char offset_high = (offset & 0xFF00) >> 8;
	index_port.outb(14); // high
	data_port.outb(offset_high);
	index_port.outb(15); // low
	data_port.outb(offset_low);
}


/*****************************************************************************
 * Methode:         CGA::getpos                                              *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Abfragem der Cursorposition                              *
 *                                                                           *
 * Rückgabewerte:   x und y                                                  *
 *****************************************************************************/
void CGA::getpos (int &x, int &y) {
    
    /* Hier muess Code eingefuegt werden */
	index_port.outb(14);
	unsigned char offset_high = data_port.inb();
	index_port.outb(15);
	unsigned char offset_low = data_port.inb();
	unsigned short offset = (unsigned short)offset_high << 8 | offset_low;
	x = offset % COLUMNS;
	y = (offset - x) / COLUMNS;

}


/*****************************************************************************
 * Methode:         CGA::show                                                *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Anzeige eines Zeichens mit Attribut an einer bestimmten  *
 *                  Stelle auf dem Bildschirm.                               *
 *                                                                           *
 * Parameter:                                                                *
 *      x,y         Position des Zeichens                                    *
 *      character   Das auszugebende Zeichen                                 *
 *      attrib      Attributbyte fuer das Zeichen                            *
 *****************************************************************************/
void CGA::show (int x, int y, char character, unsigned char attrib) {
    
    /* Hier muess Code eingefuegt werden */
	char* CGA_pos = (char*)CGA_START + 2*(y * 80 + x);
	*CGA_pos = character;
	CGA_pos++;
	*CGA_pos = attrib;
    
}


/*****************************************************************************
 * Methode:         CGA::print                                               *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Anzeige mehrerer Zeichen ab der aktuellen Cursorposition *
 *                  '\n' fuer Zeilenvorschub.                                *
 *                                                                           *
 * Parameter:                                                                *
 *      string      Auszugebende Zeichenkette                                *
 *      n           Laenger der Zeichenkette                                 *
 *      attrib      Attributbyte fuer alle Zeichen der Zeichenkette          *
 *****************************************************************************/
void CGA::print (char* string, int n, unsigned char attrib) {
    
    /* Hier muess Code eingefuegt werden */
	int x, y;
	getpos(x, y);
	char* CGA_pos = (char*)CGA_START + xy_to_offset(x, y);  // always keep it a valid offset in cga video ram
	for (int i = 0; i < n; i++) {  // deals with one char per loop which is written to CGA_pos
		if (string[i] == '\n') {
			offset_to_xy(CGA_pos - CGA_START, x, y);
			if (y == ROWS-1) {
				scrollup();
				CGA_pos = (char*)CGA_START + xy_to_offset(0, ROWS-1);
			} else {
				CGA_pos = (char*)CGA_START + xy_to_offset(0, y+1);
			}
		} else {	
			*CGA_pos = string[i];
			CGA_pos++;
			*CGA_pos = attrib;
			CGA_pos++;
			if (CGA_pos - CGA_START == COLUMNS*ROWS*2) {  // gone off the screen. need to scroll.
				scrollup();
				CGA_pos -= 2*COLUMNS;
			}
		}
	}

	offset_to_xy(CGA_pos - CGA_START, x, y);  // here x and y are reused to store the new x and y in.
	setpos(x, y); // move cursor

 
}

// wrapper for print
void CGA::printf(char* string) {
	print(string, strlen(string), STD_ATTR);
}



/*****************************************************************************
 * Methode:         CGA::scrollup                                            *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Verschiebt den Bildschirminhalt um eine Zeile nach oben. *
 *                  Die neue Zeile am unteren Bildrand wird mit Leerzeichen  *
 *                  gefuellt.                                                *
 *****************************************************************************/
void CGA::scrollup () {
    
    /* Hier muess Code eingefuegt werden */
	unsigned short* CGA_paste = (unsigned short*)CGA_START;
	unsigned short* CGA_copy = (unsigned short*)CGA_START + COLUMNS;
	for (int i = 0; i < COLUMNS*(ROWS-1); i++) {
		*CGA_paste = *CGA_copy;
		CGA_paste++;
		CGA_copy++;
	}
	for (int i = 0; i < COLUMNS; i++) {
		CGA_paste[i] = 0;
	}
    
}


/*****************************************************************************
 * Methode:         CGA::clear                                               *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Lösche den Textbildschirm.                               *
 *****************************************************************************/
void CGA::clear () {
    
    /* Hier muess Code eingefuegt werden */
	char* CGA_pos = (char*) CGA_START;
	for (int i = 0; i < 2*ROWS*COLUMNS; i++) {
		CGA_pos[i] = 0;
	}
	setpos(0, 0);
    
}


/*****************************************************************************
 * Methode:         CGA::attribute                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Hilfsfunktion zur Erzeugung eines Attribut-Bytes aus     *
 *                  Hintergrund- und Vordergrundfarbe und der Angabe, ob das *
 *                  Zeichen blinkend darzustellen ist.                       *
 *                                                                           *
 * Parameter:                                                                *
 *      bg          Background color                                         *
 *      fg          Foreground color                                         *
 *      blink       ywa/no                                                   *
 *****************************************************************************/
unsigned char CGA::attribute (CGA::color bg, CGA::color fg, bool blink) {
    
    /* Hier muess Code eingefuegt werden */
  	unsigned char attr = (unsigned char)blink;
       attr <<= 3;
	attr |= bg & 7;  // bg can only be 3 bits long
 	attr <<= 4;
	attr |= fg & 15;  // fg can be 4 bits long
	return attr;
}


// helper functions below

unsigned short CGA::xy_to_offset(int x, int y) {
	return 2 * (y * COLUMNS + x);
}

void CGA::offset_to_xy(unsigned short offset, int& x, int& y) {
	unsigned short character_offset = offset / 2;  // 1 character on screen for two bytes
	x = character_offset % COLUMNS;
	y = (character_offset - x) / COLUMNS;	
}

