#include "kernel/Paging.h"

extern "C" {
	void invalidate_tlb_entry(unsigned int*);
}

void paging_demo() {
	pg_init();
	unsigned int* ptr = pg_alloc_page();
	pg_write_protect_page(ptr);
	*ptr = 4;
}
