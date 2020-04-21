/*
 * timer.cpp
 *
 *  Created on: Aug 29, 2018
 *      Author: OS1
 */

#include "timer.h"
#include "pcb.h"
#include <dos.h>
#include "schedule.h"
#include <iostream.h>

unsigned int tsp;
unsigned int tss;
unsigned int tbp;



volatile int counter = 0;
volatile int lockFlag = 0;
volatile int requiredContextSwitch = 0;
unsigned oldTimerOFF, oldTimerSEG;
PCB *ret=0;
void lockingFlag(){ lockFlag=1;}
void unlockingFlag(){
	lockFlag=0;
   if(requiredContextSwitch)
       dispatch();
	                   }

void tick();

void interrupt timer() {
	if (!requiredContextSwitch) {
		tick();
		if(PCB::sleepPcb->first!=0){
			PCB::sleepPcb->processing();
		}
		if(counter > 0)
		   counter--;
#ifndef BCC_BLOCK_IGNORE
    	asm int 60h;
#endif

	}
	if ((PCB::running->timeSlice > 0 && counter == 0) || requiredContextSwitch) {
		if(lockFlag == 0) {
#ifndef BCC_BLOCK_IGNORE
		asm {
			mov tsp, sp // save sp
			mov tss, ss
			mov tbp, bp
		}
#endif
		PCB::running->sp = tsp;
		PCB::running->ss = tss;
		PCB::running->bp = tbp;

		if (PCB::running->status == READY)
		   Scheduler::put(PCB::running);

		PCB::running = Scheduler::get();

        if (PCB::running == 0)
       	PCB::running = PCB::idle; // idle pcb

		tsp = PCB::running->sp;
		tss = PCB::running->ss;
		tbp = PCB::running->bp;

		counter = PCB::running->timeSlice;

#ifndef BCC_BLOCK_IGNORE
		asm {
			mov sp, tsp   // restore sp
			mov ss, tss
			mov bp, tbp
		}
#endif

		requiredContextSwitch = 0;

	    }
	}
}


 void inic(){

 #ifndef BCC_BLOCK_IGNORE
 	asm{
 		pushf
 		cli
 		push es
 		push ax

 		mov ax,0
 		mov es,ax

 		mov ax, word ptr es:0022h
 		mov word ptr oldTimerSEG, ax
 		mov ax, word ptr es:0020h
 		mov word ptr oldTimerOFF, ax

 		mov word ptr es:0022h, seg timer
 		mov word ptr es:0020h, offset timer

 		mov ax, oldTimerSEG
 		mov word ptr es:0182h, ax
 		mov ax, oldTimerOFF
 		mov word ptr es:0180h, ax

 		pop ax
 		pop es
 		popf
 	}
 #endif
 }


void dispatch(){
#ifndef BCC_BLOCK_IGNORE
	asm pushf;
	asm cli;
	requiredContextSwitch = 1;
	//cout<<"YIELD "<<((unsigned long)PCB::running)/65536<<"-->";
	asm int 8h;
	//cout<<((unsigned long)PCB::running)/65536<<"\n";
	asm popf;
#endif
}

void restore(){
#ifndef BCC_BLOCK_IGNORE
	asm{
		pushf
		cli
		push es
		push ax

		mov ax,0
		mov es,ax

		mov ax, word ptr oldTimerSEG
		mov word ptr es:0022h, ax
		mov ax, word ptr oldTimerOFF
		mov word ptr es:0020h, ax

		pop ax
		pop es
		popf
	}

#endif
}



