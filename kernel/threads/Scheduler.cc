/*****************************************************************************
 *                                                                           *
 *                          S C H E D U L E R                                *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Implementierung eines einfachen Zeitscheiben-Schedulers. *
 *                  Rechenbereite Threads werden in 'readyQueue' verwaltet.  *
 *                                                                           *
 * Autor:           Michael, Schoettner, HHU, 17.1.2019                      *
 *****************************************************************************/

#include "kernel/threads/Scheduler.h"
#include "kernel/threads/IdleThread.h"
#include "kernel/Globals.h"


/*****************************************************************************
 * Methode:         Scheduler::Scheduler                                     *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Konstruktor des Schedulers. Registriert den Leerlauf-    *
 *                  Thread.                                                  *
 *****************************************************************************/
Scheduler::Scheduler () {
    initialized = false;
}


/*****************************************************************************
 * Methode:         Scheduler::schedule                                      *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Scheduler starten. Wird nur einmalig aus main.cc gerufen.*
 *****************************************************************************/
void Scheduler::schedule () {
    Thread* first;

   // Idle-Thread erzeugen und einfuegen
   IdleThread *idle = new IdleThread();
   ready (idle);

   first = (Thread*) readyQueue.dequeue();
   start (*first);
}


/*****************************************************************************
 * Methode:         Scheduler::ready                                         *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Thread in readyQueue eintragen.                          *
 *                                                                           *
 * Parameter:                                                                *
 *      that        Einzutragender Thread                                    *
 *****************************************************************************/
void Scheduler::ready (Thread* that) {
    // Thread-Wechsel durch PIT verhindern
    cpu.disable_int ();

    readyQueue.enqueue (that);

    // Thread-Wechsel durch PIT jetzt wieder erlauben
    cpu.enable_int ();
}


/*****************************************************************************
 * Methode:         Scheduler::exit                                          *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Thread ist fertig und terminiert sich selbst. Hier muss  *
 *                  nur auf den naechsten Thread mithilfe des Dispatchers    *
 *                  umgeschaltet werden. Der aktuell laufende Thread ist     *
 *                  nicht in der readyQueue.                                 *
 *****************************************************************************/
void Scheduler::exit () {
    // Thread-Wechsel durch PIT verhindern
    cpu.disable_int ();

    // hole naechsten Thread aus ready-Liste.
    Thread* next = (Thread*) readyQueue.dequeue();
    
    // next aktivieren
    dispatch (*next);

    // Interrupts werden in Thread_switch in Thread.asm wieder zugelassen
    // dispatch kehr nicht zurueck
}


/*****************************************************************************
 * Methode:         Scheduler::kill                                          *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Thread mit 'Gewalt' terminieren. Er wird aus der         *
 *                  readyQueue ausgetragen und wird dann nicht mehr aufge-   *
 *                  rufen. Der Aufrufer dieser Methode muss ein anderer      *
 *                  Thread sein.                                             *
 *                                                                           *
 * Parameter:                                                                *
 *      that        Zu terminierender Thread                                 *
 *****************************************************************************/
void Scheduler::kill (Thread* that) {
    // Thread-Wechsel durch PIT verhindern
    cpu.disable_int ();

    readyQueue.remove (that);
    
    // Thread-Wechsel durch PIT jetzt wieder erlauben
    cpu.enable_int ();
}


/*****************************************************************************
 * Methode:         Scheduler::yield                                         *
 *---------------------------------------------------------------------------*
 * Beschreibung:    CPU freiwillig abgeben und Auswahl des naechsten Threads.*
 *                  Naechsten Thread aus der readyQueue holen, den aktuellen *
 *                  aus der readyQueue austragen und auf den naechsten       *
 *                  mithilfe des Dispatchers umschalten.                     *
 *                                                                           *
 *                  Achtung: Falls nur der Idle-Thread läuft, so ist die     *
 *                           readyQueue leer.                                *
 *****************************************************************************/
void Scheduler::yield () {
    Thread* next;

    // Thread-Wechsel durch PIT verhindern
    cpu.disable_int ();

    next = (Thread*) readyQueue.dequeue ();
    
    readyQueue.enqueue ((Thread*) get_active());

    dispatch (*next);
    
    // Interrupts werden in Thread_switch in Thread.asm wieder zugelassen
    // dispatch kehr nicht zurueck
}


/*****************************************************************************
 * Methode:         Scheduler::prepare_preemption                            *
 *---------------------------------------------------------------------------*
 * Beschreibung:    CPU soll aktuellem Thread entzogen werden. Wird nur      *
 *                  aus dem Zeitgeber-Interrupt-Handler aufgerufen. Daher    *
 *                  muss nicht gegenueber Interrupts synchronisiert werden.  *
 *                                                                           *
 * Rueckgabewert:   true:   Var. fuer Thread-Wechsel in startup.asm gesetzt  *
 *                  false:  kein anderer Thread will rechnen oder Scheduler  *
 *                          ist nicht fertig initialisiert. Dann nichts tun. *
 *****************************************************************************/
bool Scheduler::prepare_preemption () {
    
    if ( initialized==false)
        return false;
    
    Thread* act  = (Thread*) get_active();
    Thread* next = (Thread*) readyQueue.dequeue ();
    
    readyQueue.enqueue (act);

    prepare_thread_switch (next);
    
    return true;
}
