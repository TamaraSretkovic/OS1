/*
 * semaphor.cpp
 *
 *  Created on: Aug 29, 2018
 *      Author: OS1
 */

#include "semaphor.h"
#include "kernels.h"
#include "timer.h"


Semaphore::Semaphore(int init){
#ifndef BCC_BLOCK_IGNORE
     asm pushf
	 asm cli
#endif
	myImpl=new KernelSem(init,this);
#ifndef BCC_BLOCK_IGNORE
     asm popf
#endif

}

Semaphore:: ~Semaphore(){
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


int Semaphore::wait(int toBlock){
	 int ret=myImpl->wait(toBlock);
    return ret;
}

void Semaphore::signal(){
lockingFlag();
myImpl->signal();
unlockingFlag();
	 }

int Semaphore::val()const{return myImpl->val();}



