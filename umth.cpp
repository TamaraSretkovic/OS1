/*
 * umth.cpp
 *
 *  Created on: Jan 21, 2019
 *      Author: OS1
 */


#include "umth.h"
#include "Thread.h"

int userMain(int argc, char* argv[]);
int status = 0;

UserMainTh::UserMainTh(int argc, char* argv[]) : Thread(), argc(argc),
		                                                  argv(argv) { }

UserMainTh::~UserMainTh() {
  waitToComplete();

}

void UserMainTh::run() {
	status = userMain(argc, argv);
}

