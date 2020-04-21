/*
 * listpcb.cpp
 *
 *  Created on: Aug 29, 2018
 *      Author: OS1
 */

#include "listpcb.h"
#include "pcb.h"
#include "schedule.h"

Listpcb::Listpcb():first(0),last(0){}

	 void Listpcb::addPcb(PCB *addpcb){
		 Node *n=new Node();
				     n->pcb=addpcb;
				     n->t=0;
				     n->next=0;

		   if(first!=0) {last->next=n;
		            last=last->next;}
		   else first=last=n;
	 }

	 void Listpcb::processing() {

	 	if(!first) return;
	 	first->t--;
	 	while(first->t<=0 && first->pcb!=PCB::idle){
	 		PCB *ret=remove();
	 						ret->status=READY;
	 						Scheduler::put(ret);
	 		if(!first) return;

	 	}
	 }
	 void Listpcb::addPcb(PCB *pcb,Time sleepTime){

		 	if(sleepTime==0) {

		 		return;
		 	}
		 	Node *novi=new Node();
		 	novi->pcb=pcb;
		 	novi->t=sleepTime;
		 	novi->next=0;
		 	if(first == 0)
		 		first = novi;
		 	else {
		 		Node *current =first, *prev = 0;
		 		while(current->t<=novi->t) {
		 			novi->t -= current->t;
		 			prev = current;
		 			current = current->next;
		 			if(current == 0)
		 				break;
		 		}

		 		if (prev == 0){
		 			novi->next = first;
		 			first = novi;
		 		}
		 		else {
		 			prev->next = novi;
		 			novi->next = current;
		 		}

		 		if(current!=0)
		 			current->t -= novi->t;

		 	}

		 	return;
	 }

	 PCB * Listpcb::remove(){
        PCB *ret=0;
        if(first!=0){
        	Node *del=first;
        	ret=first->pcb; first=first->next;
        	if(first==0)last=0;
        	del->pcb=0;
        	delete del;
        }
        return ret;
	 }
	//void Listpcb::remove(PCB* rempcb){
		// Node *curr=first,*prev=0;
		// while(curr!=0 && curr->pcb!=rempcb){prev=curr;curr=curr->next;}
		// if(curr!=0){prev->next=curr->next; delete curr;}
	 //}

	 Listpcb:: ~Listpcb(){
		 while(first!=0){
           Node *n=first->next;
           delete first;
           first=n;
		 }
		 first=0;
		 last=0;
	 }





