/*
 * kernels.h
 *
 *  Created on: Aug 29, 2018
 *      Author: OS1
 */

#ifndef KERNELS_H_
#define KERNELS_H_


#include "semaphor.h"
#include "pcb.h"

class ListSem;

class KernelSem{
public:
	Semaphore *mySem;
	int myVal;
	Listpcb *semBlocked;

	KernelSem(int init,Semaphore *mySemm);
    ~KernelSem();

	void deblockAll();
    int wait(int toBlock);
    void signal();

	int val() const{return myVal;}

protected:
	friend class Semaphore;

};


#endif /* KERNELS_H_ */
