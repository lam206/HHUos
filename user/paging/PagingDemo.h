#include "kernel/Paging.h"
#include "lib/util.h"

extern "C" {
	void invalidate_tlb_entry(unsigned int*);
}

void paging_demo() {

	pg_init();
	waitForReturn();

	unsigned int* ptr = pg_alloc_page();
	kout << "Allocated page" << endl;
	waitForReturn();

	*ptr = 4;
	kout << "Wrote a number to the start of the page" << endl;
	waitForReturn();

	pg_write_protect_page(ptr);
	kout << "Write-protected page" << endl;
	kout << "Next enter will cause another write-access. A bluescreen will be appear, showing that the old TLB entry, which allowed write-access to the page, has been invalidated." << endl;
	waitForReturn();

	*ptr = 4;
}
