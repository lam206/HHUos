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

	kout << endl;
	struct free_block *iter;

	kout << "Freispeicherliste" << endl;
	kout << " Heap-Start: " << heap_start << ", Heap-End: " << heap_end << endl;
	kout << " Block-start: " << free_start << ", block-end: " << (struct free_block*)(((char*)free_start) + free_start->size) << ", block-groesse: " << free_start->size << endl;
	iter = free_start;
	while (iter->next != 0) {
		iter = iter->next;
		kout << " Block-start: " << iter << ", block-end: " << (void*)(((char*)iter) + iter->size) << ", block-groesse: " << iter->size << endl;
	}
	kout << endl;
}


/*****************************************************************************
 * Methode:         LinkedListAllocator::alloc                               *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einen neuen Speicherblock allozieren.                    * 
 *****************************************************************************/
void * LinkedListAllocator::alloc(unsigned int req_size) {
	// i take the size fields to be the size of the respective blocks in bytes, not the free or used space in the blocks
	struct free_block* iter, *prev;
	struct used_block *allocated_block;

	unsigned int block_size = req_size + 4 + (-req_size % 4);

	// iterate over list
	// until find free_block with desired size
	
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
	if (iter->size <= block_size + 16) {  // if only 4 words or less extra, just take them.
		block_size = iter->size; // allocated_block size just becomes the size of the free block
		// remove free block from free list
		if (prev == 0) {
			free_start = iter->next;
		} else {
			prev->next = iter->next;
		}
	} else { 
		// divide large free block into used block (to be returned) and smaller free block
		struct free_block* new_free_block;
		if (prev == 0) {
			new_free_block = (struct free_block*)(((char*)free_start) + block_size);
			free_start = new_free_block;
		} else {

			new_free_block = (struct free_block*)(((char*)prev->next) + block_size);
			prev->next = new_free_block;
		}
		new_free_block->size = iter->size - block_size;
		new_free_block->next = iter->next;

	}
	allocated_block = (struct used_block*)iter;
	allocated_block->size = block_size;

	if (verbose) {
		kout << "alloc: req_size=" << req_size << ", allocated=" << block_size << ", returning addr=" << &allocated_block->data << endl;
	}
	
	return &allocated_block->data;

}


/*****************************************************************************
 * Methode:         LinkedListAllocator::free                                *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einen Speicherblock freigeben.                           *
 *****************************************************************************/
void LinkedListAllocator::free(void *ptr) {
	// free_start is made to point to block deallocated 

	struct used_block* block_to_be_freed = (struct used_block*)(((char*)ptr)-4);
	unsigned int block_size = block_to_be_freed->size;

	kout << "free: prt=" << ptr << ", size=" << block_size << endl << endl;

	struct free_block* new_free_block = (struct free_block*)block_to_be_freed;

	new_free_block->size = block_size; // simply this since size is byte-size of whole block
	new_free_block->next = free_start;
	free_start = new_free_block;

}

