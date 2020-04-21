/*
 * thread.cpp
 *
 *  Created on: Aug 29, 2018
 *      Author: OS1
 */


#include "pcb.h"
#include "timer.h"
#include "iostream.h"

class Scheduler;

Thread::Thread(StackSize stackSize, Time timeSlice){

#ifndef BCC_BLOCK_IGNORE
     asm pushf
	 asm cli
#endif
        myPCB=new PCB(this,stackSize,timeSlice);
#ifndef BCC_BLOCK_IGNORE
     asm popf
#endif
     }

Thread:: ~Thread(){
	      // waitToComplete();
	       lockingFlag();
	       if(myPCB!=0){
#ifndef BCC_BLOCK_IGNORE
     asm pushf
	 asm cli
#endif
           delete myPCB;
#ifndef BCC_BLOCK_IGNORE
     asm popf
#endif
           myPCB=0;
           }unlockingFlag();

	}

void Thread::waitToComplete(){
	//if(myPCB->status==FINISHED)return;
      myPCB->waitToComplete();
	}

void Thread::start(){
	lockingFlag();
	   myPCB->start();
	unlockingFlag();
	}

void Thread::sleep(Time timeToSleep){
       PCB::sleep(timeToSleep);
	}
