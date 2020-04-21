/*
 * ivtentry.h
 *
 *  Created on: Aug 29, 2018
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_


#include "kernelev.h"
#include "timer.h"

class KernelEv;
typedef void interrupt (*InterruptRoutine)(...);
typedef unsigned char IVTNo;


class IVTEntry{
private:
	IVTNo ivtNo;
	InterruptRoutine irOld;
	KernelEv *myKernelEv;

	void init(InterruptRoutine irNew);
	void restore();

public:
	IVTEntry(IVTNo ivtNo,InterruptRoutine irNew);
	~IVTEntry();

	void callOldRoutine();
	void setKernelEv(KernelEv* kernelEv);
	void callKernelEvSignal();

	static IVTEntry* getIVTEntry(IVTNo);
	static IVTEntry* IVT[256];

};




#endif /* IVTENTRY_H_ */
