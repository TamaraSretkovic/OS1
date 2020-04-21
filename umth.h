/*
 * umth.h
 *
 *  Created on: Jan 21, 2019
 *      Author: OS1
 */

#ifndef UMTH_H_
#define UMTH_H_

#include "Thread.h"

class Thread;

class UserMainTh : public Thread {
public:
    UserMainTh(int argc, char* argv[]);
    ~UserMainTh();

	void run();

private:
	int argc;
    char** argv;
};


#endif /* UMTH_H_ */
