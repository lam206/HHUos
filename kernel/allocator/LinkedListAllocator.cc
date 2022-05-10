/*****************************************************************************
 *                                                                           *
 *                  L I N K E D L I S T A L L O C A T O R                    *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einfache Speicherverwaltung, welche den freien Speicher  *
 *                  mithilfe einer einfach verketteten Liste verwaltet.      *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 13.6.2020                        *
 *****************************************************************************/

#include <stddef.h>
#include "kernel/Globals.h"
#include "kernel/allocator/LinkedListAllocator.h"

#define HEAP_MIN_FREE_BLOCK_SIZE 64         // min. Groesse eines freien Blocks


/*****************************************************************************
 * Methode:         LinkedListAllocator::init                                *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Liste der Freispeicherbloecke intitialisieren.           *
 *                  Anker zeigt auf ein Dummy-Element. Danach folgt          *
 *                  ein Block der den gesamten freien Speicher umfasst.      *
 *                                                                           *
 *                  Wird automatisch aufgerufen, sobald eine Funktion der    *
 *                  Speicherverwaltung erstmalig gerufen wird.               *
 *****************************************************************************/
void LinkedListAllocator::init() {

     /* Hier muess Code eingefuegt werden */
	free_start = (struct free_block*)0x300000;
	free_start->size = 0x100000;
	free_start->next = 0;


}


/*****************************************************************************
 * Methode:         LinkedListAllocator::dump_free_memory                    *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Ausgabe der Freispeicherliste. Zu Debuggingzwecken.      *
 *****************************************************************************/
void LinkedListAllocator::dump_free_memory() {

     /* Hier muess Code eingefuegt werden */

}


/*****************************************************************************
 * Methode:         LinkedListAllocator::alloc                               *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einen neuen Speicherblock allozieren.                    * 
 *****************************************************************************/
void * LinkedListAllocator::alloc(unsigned int req_size) {
	struct free_block* iter, *prev;
	unsigned int block_size = req_size + 4 + (4 - (req_size % 4));

     /* Hier muess Code eingefuegt werden */
	// iterate over list
	// until find free_block with desired size
	//
	//
	
	prev = 0;
	iter = free_start;
	while (iter->size < block_size) {
		prev = iter;
		iter = iter->next;
		if (iter == 0) {
			return 0;  // ran out of space
		}
	}

	// found free space
	if (iter->size < block_size + 4) {  // space too small to make sense to leave it free
		if (prev == 0) {
			free_start = iter->next;
		} else {
			prev->next = iter->next;
		}
		// size stays the same. whole free block used.
	} else {
		struct free_block* new_free_block;
		if (prev == 0) {
			free_start += block_size;
			new_free_block = free_start;
		} else {
			prev->next += block_size;
			new_free_block = prev->next;
		}
		new_free_block->size = iter->size - block_size;
		new_free_block->next = iter->next;

		//size changes
		iter->size = block_size;
	}
	
	return iter+4;


}


/*****************************************************************************
 * Methode:         LinkedListAllocator::free                                *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einen Speicherblock freigeben.                           *
 *****************************************************************************/
void LinkedListAllocator::free(void *ptr) {

     /* Hier muess Code eingefuegt werden */
	struct free_block* new_free_block = (struct free_block*)ptr-4;
	new_free_block->next = free_start;
	free_start = new_free_block;

}

