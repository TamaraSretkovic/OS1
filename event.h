/*
 * event.h
 *
 *  Created on: Aug 29, 2018
 *      Author: OS1
 */

#ifndef EVENT_H_
#define EVENT_H_


#include "thread.h"
#include "ivtentry.h"

class IVTEntry;

typedef unsigned char IVTNo;
class KernelEv;

class Event{
public:
	Event(IVTNo ivtNo);
	~Event();

	void wait();

protected:
	friend class KernelEv;
	void signal(); //can call KernelEv

private:
	KernelEv *myImpl;

};


//typedef int callOldRout;

#define PREPAREENTRY(IVTNo, callOldRout)\
void interrupt interruptRoutine##IVTNo(...);\
IVTEntry newEntry##IVTNo(IVTNo, interruptRoutine##IVTNo);\
void interrupt interruptRoutine##IVTNo(...){\
if (callOldRout == 1)\
	   IVTEntry::IVT[IVTNo]->callOldRoutine();\
	   IVTEntry::IVT[IVTNo]->callKernelEvSignal();\
	   dispatch();\
}


#endif /* EVENT_H_ */
