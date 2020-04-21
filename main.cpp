/*
 * main.cpp
 *
 *  Created on: Aug 29, 2018
 *      Author: OS1
 */


#include "umth.h"
#include "timer.h"
#include "pcb.h"
#include <iostream.h>

extern int userMain (int argc, char* argv[]);
extern int status;

int main(int argc, char* argv[]){

inic();

Thread *t=new Thread();
PCB::running=new PCB(t,defaultStackSize,defaultTimeSlice);

UserMainTh* um = new UserMainTh(argc, argv);
um->start();
delete t;
delete um;
delete PCB::sleepPcb;
int i=status;
restore();

//cout<<"prosao resstore"+i;

return i;
}


