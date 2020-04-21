/*
 * pcb.h
 *
 *  Created on: Aug 29, 2018
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_


#include "thread.h"
#include "listpcb.h"

#define NOTREADY 0
#define READY 1
#define BLOCKED 2
#define SLEEP 3
#define FINISHED 4
#define IDLE 5

class Listpcb;

class PCB{

public:
	unsigned ss, sp, bp, timeSlice, *stack;
	int status;

	Thread *myThread;
	Listpcb *blocked;

public:
	static PCB *idle;
	static PCB *running;
	static Listpcb *sleepPcb;


public:
	PCB();
	PCB(Thread *myTh,StackSize stackSize, Time timeSl);
	~PCB();
    static void wrapper();

    void start();
    void waitToComplete();

    static void sleep(Time timeToSleep);
    static void idleThread();

protected:
    friend class Thread;

};



#endif /* PCB_H_ */
