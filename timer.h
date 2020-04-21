/*
 * timer.h
 *
 *  Created on: Aug 29, 2018
 *      Author: OS1
 */

#ifndef TIMER_H_
#define TIMER_H_


extern volatile int lockFlag;
extern volatile int reqiredContextSwitch;

 void lockingFlag();
 void unlockingFlag();


	 void inic();
	 void restore();
	 void interrupt timer();



#endif /* TIMER_H_ */
