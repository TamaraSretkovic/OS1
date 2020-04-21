/*
 * listpcb.h
 *
 *  Created on: Aug 29, 2018
 *      Author: OS1
 */

#ifndef LISTPCB_H_
#define LISTPCB_H_


#include "thread.h"

class PCB;

class Listpcb{
	private:

	 struct Node{
		 PCB *pcb;
		 Time t;
		 Node *next;
	 };
	 friend class PCB;
	public:
	 Node *first, *last;
public:
	 Listpcb();


	 void addPcb(PCB *addpcb);
	 void addPcb(PCB *addpcb,Time time);
	 PCB * remove();
	 void remove(Node* rempcb);

    void processing();
    //Time time(){return first->t;}
    //int isZero(){return first->t==0?1:0;}

	 ~Listpcb();

};



#endif /* LISTPCB_H_ */
