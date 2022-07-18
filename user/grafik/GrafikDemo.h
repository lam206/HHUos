#include "kernel/Globals.h"
#include "user/grafik/VBEdemo.h"
#include "kernel/threads/IdleThread.h"

void vbe_demo() {
	VBEdemo *v = new VBEdemo();
	IdleThread *idle = new IdleThread();

	scheduler.ready(idle);
	scheduler.ready(v);

	scheduler.schedule();
}
