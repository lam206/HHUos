#include "kernel/threads/IdleThread.h"
#include "user/preemptive/Counter.h"
#include "user/preemptive/Player.h"

void semaphore_demo() {
	Semaphore *s = new Semaphore(1);

    Counter *counter = new Counter(0, s);                                                                 
    Counter *counter2 = new Counter(10, s);                                                                   
    Counter *counter3 = new Counter(20, s);    
    Player *player = new Player();   
    IdleThread *idle = new IdleThread();                                                                                                
                                                                                                                    
    scheduler.ready(idle);                                                                                         
    scheduler.ready(counter);
    scheduler.ready(counter2);
    scheduler.ready(counter3);
    scheduler.ready(player);
    scheduler.schedule();

}

	
