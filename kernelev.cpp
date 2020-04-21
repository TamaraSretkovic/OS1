/*
 * kernelev.cpp
 *
 *  Created on: Aug 29, 2018
 *      Author: OS1
 */

#include "event.h"
#include "ivtentry.h"
#include "pcb.h"
#include "timer.h"
#include "schedule.h"
#include <iostream.h>



KernelEv::KernelEv(IVTNo ivtNo){
	myIvtNo=ivtNo;
	val=0;
	myPcb=PCB::running;
	IVTEntry::getIVTEntry(ivtNo)->setKernelEv(this);

}
	KernelEv::~KernelEv(){
		signal();
		if(	IVTEntry::getIVTEntry(myIvtNo)==this)
		IVTEntry::getIVTEntry(myIvtNo)->setKernelEv(0);
	}
	void KernelEv::wait() {
		lockingFlag();
		if (PCB::running == myPcb) {
			if (val == 0) {
	           myPcb->status = BLOCKED;
	           unlockingFlag();
	           dispatch();
	           return;
			}
			else {
			   val = 0;
			}
		}
		unlockingFlag();
	}

	void KernelEv::signal() {
		if (myPcb->status == BLOCKED){
		    myPcb->status = READY;

		    Scheduler::put(myPcb);

		} else
			val = 1;

	}



