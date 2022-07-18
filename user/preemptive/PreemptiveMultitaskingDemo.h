#include "kernel/threads/IdleThread.h"
#include "user/preemptive/Counter.h"
#include "user/preemptive/Player.h"

void preemptive_multitasking_demo() {

    Counter *counter = new Counter(0);                                                                 
    Counter *counter2 = new Counter(10);                                                                   
    Counter *counter3 = new Counter(20);    
    Player *player = new Player();   
    IdleThread *idle = new IdleThread();                                                                                                
                                                                                                                    
    scheduler.ready(idle);                                                                                         
    scheduler.ready(counter);
    scheduler.ready(counter2);
    scheduler.ready(counter3);
    scheduler.ready(player);
    scheduler.schedule();

}

