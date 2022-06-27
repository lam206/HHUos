/*****************************************************************************
 *                                                                           *
 *                              C O R O U T I N E                            *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Implementierung eines Koroutinen-Konzepts.               *
 *                  Die Koroutinen sind miteinander verkettet, weswegen die  *
 *                  Klasse Thread ein Subtyp von 'Chain' ist.             *
 *                                                                           *
 *                  Im Konstruktor wird der initialie Kontext der Koroutine  *
 *                  eingerichtet. Mit 'start' wird ein Koroutine aktiviert.  *
 *                  Das Umschalten auf die naechste Koroutine erfolgt durch  *
 *                  Aufruf von 'switchToNext'.                               *
 *                                                                           *
 *                  Um bei einem Koroutinenwechsel den Kontext sichern zu    *
 *                  koennen, enthaelt jedes Koroutinenobjekt eine Struktur   *
 *                  ThreadState, in dem die Werte der nicht-fluechtigen   *
 *                  Register gesichert werden koennen.                       *
 *                                                                           *
 * Autor:           Michael, Schoettner, HHU, 13.08.2020                     *
 *****************************************************************************/

#include "kernel/threads/Thread.h"
#include "kernel/Globals.h"

// Funktionen, die auf der Assembler-Ebene implementiert werden, muessen als
// extern "C" deklariert werden, da sie nicht dem Name-Mangeling von C++
// entsprechen.
extern "C"
{
    void Thread_start  (struct ThreadState* regs);
    void Thread_switch (struct ThreadState* regs_now,
                           struct ThreadState* reg_then);
    
}


/*****************************************************************************
 * Prozedur:        Thread_init                                         *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Bereitet den Kontext eines Threads fuer den ersten       *
 *                  Aufruf vor. Diese Methode wird jetzt nur noch vom erten  *
 *                  Thread genutzt, das ist der Idle-Thread der zuerst in    *
 *                  Ready-Queue eingetragen wird.                            *
 *                  Der Stackframe muss kompatibel zum Interrupt-Stackframe  *
 *                  sein, da später nur noch im Timer-Interrupt umgechaltet  *
 *                  wird (iehe startup.asm).                                 *
 *****************************************************************************/
void Thread_init (struct ThreadState* regs, unsigned int* stack,
                       void (*kickoff)(Thread*), void* object) {
    
    register unsigned int **sp = (unsigned int**)stack;
    unsigned int flags;
    
    // Stack initialisieren. Es soll so aussehen, als waere soeben die
    // eine Funktion aufgerufen worden, die als Parameter den Zeiger
    // "object" erhalten hat.
    // Da der Funktionsaufruf simuliert wird, kann fuer die Ruecksprung-
    // adresse nur ein unsinniger Wert eingetragen werden. Die aufgerufene
    // Funktion muss daher dafuer sorgen, dass diese Adresse nie benoetigt
    // wird, sie darf also nicht terminieren, sonst kracht's.
    
    *(--sp) = (unsigned int*)object;    // Parameter
    *(--sp) = (unsigned int*)0x131155; // Ruecksprungadresse
    
    // Nun legen wir noch die Adresse der Funktion "kickoff" ganz oben auf
    // den Stack. Wenn dann bei der ersten Aktivierung dieser Koroutine der
    // Stackpointer so initialisiert wird, dass er auf diesen Eintrag
    // verweist, genuegt ein ret, um die Funktion kickoff zu starten.
    // Genauso sollen auch alle spaeteren Threadwechsel ablaufen.
    
    *(--sp) = (unsigned int*)kickoff;   // Adresse
    
    // Initialisierung der Struktur ThreadState mit den Werten, die die
    // nicht-fluechtigen Register beim ersten Starten haben sollen.
    // Wichtig ist dabei nur der Stackpointer.
    
    regs->ebx = 0;
    regs->esi = 0;
    regs->edi = 0;
    regs->ebp = 0;
    regs->esp = sp;

    // nachfolgend die fluechtige Register
    // wichtig fuer preemptives Multitasking
    regs->eax = 0;
    regs->ecx = 0;
    regs->edx = 0;
    
    // flags initialisieren, Stackframe wie bei einem Interrupt
    asm volatile ("pushf;"
                  "pop %0;" : "=a"(flags)
                  );
    regs->efl = (void*)flags;
}


/*****************************************************************************
 * Funktion:        kickoff                                                  *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Funktion zum Starten einer Korutine. Da diese Funktion   *
 *                  nicht wirklich aufgerufen, sondern nur durch eine        *
 *                  geschickte Initialisierung des Stacks der Koroutine      *
 *                  angesprungen wird, darf er nie terminieren. Anderenfalls *
 *                  wuerde ein sinnloser Wert als Ruecksprungadresse         * 
 *                  interpretiert werden und der Rechner abstuerzen.         *
 *****************************************************************************/
void kickoff (Thread* object) {
    object->run();
    
    // object->run() kehrt hoffentlich nie hierher zurueck
    for (;;) {}
}


/*****************************************************************************
 * Methode:         Thread::Thread                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Initialer Kontext einer Koroutine einrichten.            *
 *                                                                           *
 * Parameter:                                                                *
 *      stack       Stack für die neue Koroutine                             *
 *****************************************************************************/
unsigned int tid_gen = 0;

Thread::Thread () {
	this->tid = tid_gen;
	tid_gen++;
	unsigned int *stack = (unsigned int*)allocator.alloc(4000);
    Thread_init (&regs, stack+4000, kickoff, this);
 }


/*****************************************************************************
 * Methode:         Thread::switchTo	                                     *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Auf die nächste Koroutine umschalten.                    *
 *****************************************************************************/
void Thread::switchTo (Thread& next) {

    /* hier muss Code eingefügt werden */
	// kout << "Thread::switchTo" << endl;
	//kout << "this: ";
	// kout << "&this->regs: " << &this->regs << ". &(next.regs): " << &(next.regs) << endl;
	Thread_switch(&this->regs, &(next.regs));

}


/*****************************************************************************
 * Methode:         Thread::start                                         *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Aktivierung der Koroutine.                               *
*****************************************************************************/
void Thread::start () {
    
    /* hier muss Code eingefügt werden */
	Thread_start(&regs);
    
}



