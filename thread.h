/*
 * thread.h
 *
 *  Created on: Aug 29, 2018
 *      Author: OS1
 */

#ifndef THREAD_H_
#define THREAD_H_

typedef unsigned long StackSize;

const StackSize defaultStackSize=4096;

typedef unsigned int Time; //time, x 55ms
const Time defaultTimeSlice=2;

class PCB; //Kernel's implementation of a user's thread

class Thread{

private: PCB* myPCB;

public:
	void start();
	void waitToComplete();
	virtual ~Thread();

	static void sleep(Time timeToSleep);


protected:
	friend class PCB;
public:
	Thread (StackSize stackSize=defaultStackSize, Time timeSlice=defaultTimeSlice);
	virtual void run(){}




};

void dispatch();



#endif /* THREAD_H_ */
