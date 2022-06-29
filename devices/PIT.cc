/*****************************************************************************
 *                                                                           *
 *                                   P I T                                   *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Programmable Interval Timer.                             *
 *                                                                           *
 * Autor:           Michael Schoettner, 25.8.2016                            *
 *****************************************************************************/

#include "devices/PIT.h"
#include "kernel/IOport.h"
#include "kernel/Globals.h"


/*****************************************************************************
 * Methode:         PIT::interval                                            *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Zeitinervall programmieren.                              *
 *                                                                           *
 * Parameter:                                                                *
 *      us:         Zeitintervall in Mikrosekunden, nachdem periodisch ein   * 
 *                  Interrupt erzeugt werden soll.                           *
 *****************************************************************************/
void PIT::interval (int us) {

    /* hier muss Code eingefuegt werden */
	unsigned int reload_value = us / time_base;  // since reload_value * time_base = us
	control.outb(0b00110110);

	unsigned int lobyte_mask = (1 << 8)-1;
	channel0.outb((unsigned char) (reload_val & lobyte_mask));  // lobyte
	channel0.outb((unsigned char) ((reload_val >> 8) & lobyte_mask));  // then hibyte (access mode 11)
    
}


/*****************************************************************************
 * Methode:         PIT::plugin                                              *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Unterbrechungen fuer den Zeitgeber erlauben. Ab sofort   *
 *                  wird bei Ablauf des definierten Zeitintervalls die       *
 *                  Methode 'trigger' aufgerufen.                            *
 *****************************************************************************/
void PIT::plugin () {

    /* hier muss Code eingefuegt werden */
	intdis.assign(intdis.pit, *this);
	pic.allow(pic.pit);


}


/*****************************************************************************
 * Methode:         PIT::trigger                                             *
 *---------------------------------------------------------------------------*
 * Beschreibung:    ISR fuer den Zeitgeber. Wird aufgerufen, wenn der        * 
 *                  Zeitgeber eine Unterbrechung ausloest. Anzeige der Uhr   *
 *                  aktualisieren und Thread wechseln durch Setzen der       *
 *                  Variable 'forceSwitch', wird in 'int_disp' behandelt.    *
 *****************************************************************************/
void PIT::trigger () {

    /* hier muss Code eingefuegt werden */
    
    // alle 10ms, Systemzeit weitersetzen
    systime++;

    // Bei jedem Tick einen Threadwechsel ausloesen.
    // Aber nur wenn der Scheduler bereits fertig intialisiert wurde
    // und ein weiterer Thread rechnen moechte
    if ( scheduler.isInitialized() ) {
        if ( scheduler.prepare_preemption() )
            forceSwitch=1;
    }
}


