/*
 * pcb.cpp
 *
 *  Created on: Aug 29, 2018
 *      Author: OS1
 */


#include "pcb.h"
#include "schedule.h"
#include <dos.h>
#include "timer.h"
#include <iostream.h>

PCB* PCB::idle=0;
PCB* PCB::running=0;
Listpcb *PCB::sleepPcb=new Listpcb();

PCB::PCB(){

	 this->timeSlice = 1;
	 myThread=0;
	 blocked=0;

	 stack=new unsigned[defaultStackSize];
	 status=IDLE;
	 PCB::idle=this;
	 ss=bp=sp=0;

	 stack[defaultStackSize-1]=0x200;

#ifndef BCC_BLOCK_IGNORE
	stack[defaultStackSize - 2] = FP_SEG(&(idleThread));
	stack[defaultStackSize - 3] = FP_OFF(&(idleThread));
	sp = bp = FP_OFF(stack + defaultStackSize - 12); // offset for all registers
	ss = FP_SEG(stack + defaultStackSize - 12);
    #endif

}

PCB::PCB(Thread *myTh,StackSize stackSize, Time timeSl){
	if(PCB::idle==0)PCB::idle=new PCB();
    if(stackSize>defaultStackSize)
		stackSize = defaultStackSize;
	stack=new unsigned[stackSize];

#ifndef BCC_BLOCK_IGNORE
	stack[stackSize-1]=FP_SEG(myTh);     //stack init
	stack[stackSize-2]=FP_OFF(myTh);

	stack[stackSize-5]=0x200;           //PSW
	stack[stackSize-6]=FP_SEG(&(wrapper));
	stack[stackSize-7]=FP_OFF(&(wrapper));

	ss=FP_SEG(stack+stackSize-16);
	sp=FP_OFF(stack+stackSize-16);
    bp=FP_SEG(stack+stackSize-16);
#endif

	status=NOTREADY;
	timeSlice=timeSl;
	blocked=new Listpcb();
	myThread=myTh;
}

void PCB::wrapper(){
	 running->myThread->run();
	 lockingFlag();
	 //int i=0;
	 //cout<<"gotov run i krece oslobadjanje "<<((unsigned long)PCB::running)/65536<<"\n";
	 while(running!=0 && running->blocked->first!=0){
		 PCB *curr=running->blocked->remove();
		 curr->status=READY;
		 Scheduler::put(curr);
		// i++;
	 }
	// cout<<"i= "<<i<<"   "<<((unsigned long)PCB::running)/65536<<"\n";
	 //if(running!=0)
	 running->status=FINISHED;

	 unlockingFlag();
	 dispatch();

}

void PCB::waitToComplete(){
        lockingFlag();
       // cout<<"WAIT "<<((unsigned long)PCB::running)/65536<<"-->"<<((unsigned long)this)/65536<<"\n";
	    if(status!=NOTREADY && status!=FINISHED && this!=PCB::running && this!=PCB::idle){
	    	PCB::running->status=BLOCKED;
		    blocked->addPcb(PCB::running);
		    unlockingFlag();

		    dispatch();

	    }
	    else unlockingFlag();
	}


void PCB::start(){
	if(status==NOTREADY){
	   status=READY;
	   //cout<<"STARTED "<<((unsigned long)PCB::running)/65536<<"-->"<<((unsigned long)this)/65536<<"\n";
	   Scheduler::put(this);}
	}


void PCB::sleep(Time timeToSleep){
	lockingFlag();
		//cout<<"SLEEP "<<((unsigned long)PCB::running)/65536<<"\n";
        PCB::running->status=SLEEP;
        if(PCB::sleepPcb==0)PCB::sleepPcb=new Listpcb();
        PCB::sleepPcb->addPcb(PCB::running,timeToSleep);
     unlockingFlag();
        dispatch();
	}

PCB::~PCB(){
	if(stack!=0){
		delete []stack;
		stack=0;
	}
	if(blocked!=0){
		delete blocked;
		blocked=0;
	}

}

void PCB::idleThread(){
	while(1){
		for(int i=0;i<3000;i++)
			for(int j=0;j<5000;j++);
	}
}

