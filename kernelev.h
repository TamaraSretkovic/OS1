/*
 * kernelev.h
 *
 *  Created on: Aug 29, 2018
 *      Author: OS1
 */

#ifndef KERNELEV_H_
#define KERNELEV_H_

#include "ivtentry.h"
#include "pcb.h"
#include "event.h"

typedef unsigned char IVTNo;

class KernelEv{
private:
	IVTNo myIvtNo;
	int val;
	PCB *myPcb;
public:
	KernelEv(IVTNo ivtNo);
	~KernelEv();

	void signal();
	void wait();

};


#endif /* KERNELEV_H_ */
