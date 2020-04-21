/*
 * schedule.h
 *
 *  Created on: Aug 29, 2018
 *      Author: OS1
 */

#ifndef SCHEDULE_H_
#define SCHEDULE_H_


// Obavezno odbrati HUGE mem. model kao sto je prikazano u uputstvu za podesavanje BC31 okruzenja. Takodje, podesiti putanje ka .lib i .h fajlovima kao i ostale parametre prema uputstvu!
// Dodati APLICAT.LIB u projekat: (Project->Add Item...), promeniti Name filter u *.* kako bi se videli svi fajlovi i odabrati APLICAT.LIB. Zatim pozvati Compile->Build All
class PCB;

class Scheduler{
public:
	static void put (PCB *);
	static PCB* get ();
};


#endif /* SCHEDULE_H_ */
