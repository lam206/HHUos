/*****************************************************************************
 *                                                                           *
 *                               G L O B A L S                               *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Globale Variablen des Systems.                           *
 *                                                                           *
 * Autor:           Michael Schoettner, 30.7.16                              *
 *****************************************************************************/
#ifndef __Globals_include__
#define __Globals_include__

#include "kernel/CPU.h"
#include "kernel/interrupts/PIC.h"
#include "kernel/allocator/BumpAllocator.h"
#include "kernel/allocator/LinkedListAllocator.h"
#include "devices/PCSPK.h"
#include "devices/PIT.h"
#include "kernel/BIOS.h"
#include "devices/CGA_Stream.h"
#include "devices/Keyboard.h"
#include "kernel/interrupts/IntDispatcher.h"
#include "kernel/threads/Scheduler.h"
#include "devices/VESA.h"



//
// Kernel-Klassen
//
extern CPU              cpu;        // CPU-spezifische Funktionen
extern PIC              pic;        // Interrupt-Controller
extern IntDispatcher    intdis;     // Unterbrechungsverteilung
extern Scheduler        scheduler;  // Scheduler
extern BIOS             bios;       // Schnittstelle zum 16-Bit BIOS
//extern BumpAllocator         allocator;       
extern LinkedListAllocator   allocator;       
extern int verbose; // 1 = print stuff, 0 = don't print stuff
extern unsigned int     total_mem;  // RAM total
extern unsigned long    systime;    // wird all 10ms hochgezaehlt
extern bool             forceSwitch;// gesetzt in Timer-Interrupt,
                                    // wenn Thread-Wechsel erfolgen soll

//
// Geräte-Treiber-Klassen
//
extern PCSPK            pcspk;      // PC-Lautsprecher
extern CGA_Stream       kout;       // Ausgabe-Strom fuer Kernel
extern Keyboard         kb;         // Tastatur
extern VESA             vesa;       // VESA-Treiber
extern PIT              pit;        // Zeitgeber

#endif
