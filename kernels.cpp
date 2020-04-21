/*
 * kernels.cpp
 *
 *  Created on: Aug 29, 2018
 *      Author: OS1
 */

#include "kernels.h"
#include "schedule.h"
#include "timer.h"


KernelSem::KernelSem(int init, Semaphore *mySemm){
	myVal=init;
	mySem=mySemm;
	semBlocked=new Listpcb();
}

	void KernelSem::deblockAll(){
		if(semBlocked!=0){
		while(semBlocked->first!=0){
			signal();
		}
		 delete semBlocked;
		 semBlocked=0;
		}
	}
	KernelSem::~KernelSem(){
		if(semBlocked!=0)
			deblockAll();
		delete semBlocked;
	}
    int KernelSem::wait(int toBlock){
    	lockingFlag();
    	if(toBlock!=0){
    		myVal--;
    		if(myVal<0){
    			PCB::running->status=BLOCKED;
    			semBlocked->addPcb(PCB::running);
				unlockingFlag();
    			dispatch();
    			return 1;
    		}
			unlockingFlag();
    		return 0;
    	}

    	else if(myVal<=0){
			unlockingFlag();
    		return -1;}
    	   else{
    		   myVal--;
				unlockingFlag();
    		   return 0;
    	      }
    }
    void KernelSem::signal(){
    	myVal++;
    	if(myVal<=0){
    		PCB* ret=semBlocked->remove();
    		ret->status=READY;
    		Scheduler::put(ret);
    	}
    }





