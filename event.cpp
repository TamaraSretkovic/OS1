/*
 * event.cpp
 *
 *  Created on: Aug 29, 2018
 *      Author: OS1
 */

#include "event.h"
#include"kernelev.h"
#include "timer.h"

    Event::Event(IVTNo ivtNo){
#ifndef BCC_BLOCK_IGNORE
     asm pushf
	 asm cli
#endif
    	myImpl=new KernelEv(ivtNo);
#ifndef BCC_BLOCK_IGNORE
     asm popf
#endif
    }

	Event::~Event(){
#ifndef BCC_BLOCK_IGNORE
     asm pushf
	 asm cli
#endif
		if(myImpl!=0){
		delete myImpl;
		myImpl=0;}
#ifndef BCC_BLOCK_IGNORE
     asm popf
#endif

	}

	void Event::wait(){myImpl->wait();}

	void Event::signal(){
		lockingFlag();
		myImpl->signal();
		unlockingFlag();
	}


