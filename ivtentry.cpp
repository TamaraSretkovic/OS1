/*
 * ivtentry.cpp
 *
 *  Created on: Aug 29, 2018
 *      Author: OS1
 */

#include <dos.h>
#include "ivtentry.h"


IVTEntry* IVTEntry::IVT[256]={0};

IVTEntry::IVTEntry(IVTNo ivtNo, InterruptRoutine irNew) {
    lockingFlag();
	this->ivtNo = ivtNo;
	init(irNew);
	IVT[ivtNo] = this;
	unlockingFlag();
}

IVTEntry::~IVTEntry() {
	lockingFlag();
	restore();
	IVT[ivtNo] = 0;
	ivtNo = -1;
	irOld = 0;
	myKernelEv = 0;
	unlockingFlag();
}

void IVTEntry::init(InterruptRoutine irNew) {
#ifndef BCC_BLOCK_IGNORE
	asm pushf
	asm cli
	irOld = getvect(ivtNo);
	setvect(ivtNo, irNew);
	asm popf
#endif
}


void IVTEntry::restore() {
#ifndef BCC_BLOCK_IGNORE
	asm pushf
	asm cli
	setvect(ivtNo, irOld);
	asm popf
#endif
}

IVTEntry* IVTEntry::getIVTEntry(IVTNo ivtNo) {
	return IVTEntry::IVT[ivtNo];
}

void IVTEntry::callOldRoutine() {
	if(irOld != 0)
	   (*irOld)();
}

void IVTEntry::setKernelEv(KernelEv* kernelEv) {
	myKernelEv = kernelEv;
}

void IVTEntry::callKernelEvSignal() {
	if(myKernelEv != 0)
	   myKernelEv->signal();
}




