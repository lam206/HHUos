#include "lib/Queue.h"
#include "kernel/Globals.h"


void Queue::enqueue (Chain* item) {  // don't need to check if empty or not
	// have pointer to tail
	// take tail next pointer and set that to item
	
	if (item->next != 0) {
		item->next = 0;  // making sure tail of new element is zero (enqueue is for adding elements not concatenating Queues)
	}
	
	*tail = item;	
	tail = &item->next;
}


Chain* Queue::dequeue () {
	// take head
	// set head to next of head
	
	if (this->head == 0) {
		kout << "Error. Queue is empty." << endl;
		return 0;
	}
	Chain *newHead = this->head->next;
	Chain *oldHead = this->head;
	this->head = newHead;
	if (newHead == 0) {
		tail = &this->head;
	}
	oldHead->next = 0;  // Notion of next for a dequeued thing doesn't make sense. The element no longer has a next.
	return oldHead;

}


void Queue::remove (Chain* item) {
	// loop over list until find the element in next
	// make next to the one after it 
	
	if (this->head == item) {
		this->head = this->head->next;
		return;
	}
	
	Chain *iter = this->head;
	while (iter->next != 0) {
		if (iter->next == item) {
			Chain *newNext = item->next;
			iter->next = newNext;
			break;
		}
		iter = iter->next;
	}

}


char Queue::is_empty() {
	if (this->head == 0) {
		return 1; // Queue is empty
	} else {
		return 0; // Queue is not empty
	}
}

