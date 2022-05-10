/*****************************************************************************
 *                                                                           *
 *                            A L L O C A T O R                              *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einfache Speicherverwaltung. 'new' und 'delete' werden   *
 *                  durch Ueberladen der entsprechenden Operatoren           *
 *                  realisiert.                                              *
 *                                                                           *
 * Memory-Laylout                                                            *
 *                                                                           *
 *                  boot.asm                                                 *
 *                      0x07c0: Bootsector vom BIOS geladen                  *
 *                      0x0060: Boot-Code verschiebt sich hier hin           *
 *                      0x9000: Setup-Code (max. 64K inkl. Stack) vom        *
 *                              Bootsector-Code geladen                      *
 *                  setup.asm                                                *
 *                      0x1000: System-Code (max. 512K) geladen              *
 *                  System-Code                                              *
 *                    0x100000:	System-Code, kopiert nach Umschalten in      *
 *                              den Protected Mode kopiert (GRUB kann nur    *
 *                              an Adressen >1M laden)                       *
 *           Globale Variablen: Direkt nach dem Code liegen die globalen     *
 *                              Variablen.                                   *
 *                        Heap:                                              *
 *                    0x300000:	Start-Adresse der Heap-Verwaltung            *
 *                    0x400000: Letzte Adresse des Heaps                     *
 *                                                                           *
 * Achtung:         Benötigt einen PC mit mindestens 4 MB RAM!               *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 13.6.2020                        *
 *****************************************************************************/
#ifndef __Allocator_include__
#define __Allocator_include__



class Allocator {
    
private:
      Allocator(Allocator &copy); // Verhindere Kopieren

public:
      unsigned int total_mem;  // i added this
      unsigned int heap_start;
      unsigned int heap_end;
      unsigned int heap_size;
      unsigned int initialized;

      Allocator ();

      virtual void init () = 0;        
      virtual void dump_free_memory () = 0;
      virtual void* alloc (unsigned int req_size) = 0;
      virtual void free (void *ptr) = 0;

};

#endif
