#include "lib/Queue.h"


void Queue::enqueue (Chain* item) {  // don't need to check if empty or not
	// have pointer to tail
	// take tail next pointer and set that to item
	
	*tail = item;	
	tail = &item->next;
}


Chain* Queue::dequeue () {
	// take head
	// set head to next of head
	
	Chain *newHead = this->head->next;
	Chain *oldHead = this->head;
	this->head = newHead;
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


