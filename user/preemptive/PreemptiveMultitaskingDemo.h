#include "kernel/threads/IdleThread.h"
#include "user/preemptive/Counter.h"
#include "user/preemptive/Player.h"

void preemptive_multitasking_demo() {

    Semaphore s(1);

    Counter counter(0, &s);
    Counter counter2(10, &s);
    Counter counter3(20, &s);
    Player player;
    IdleThread idle;

    scheduler.ready(&idle);
    scheduler.ready(&counter);
    scheduler.ready(&counter2);
    scheduler.ready(&counter3);
    scheduler.ready(&player);
    scheduler.schedule();
    
}

