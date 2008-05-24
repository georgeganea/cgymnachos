// threadtest.cc 
//	Simple test case for the threads assignment.
//
//	Create two threads, and have them context switch
//	back and forth between themselves by calling Thread::Yield, 
//	to illustratethe inner workings of the thread system.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "synch.h"


//----------------------------------------------------------------------
// SimpleThread
// 	Loop 5 times, yielding the CPU to another ready thread 
//	each iteration.
//
//	"which" is simply a number identifying the thread, for debugging
//	purposes.
//----------------------------------------------------------------------

Lock* lock = new Lock("variable lock");
int value = 5;
void
SimpleLockThread(int which)
{
    for (int num = 0; num < 5; num++) {
    	lock->Acquire();
    	printf("Incremented\n");
    	value++;
    	lock->Release();
    	currentThread->Yield();
    }
}


//----------------------------------------------------------------------
// ThreadTest
// 	Set up a ping-pong between two threads, by forking a thread 
//	to call SimpleThread, and then calling SimpleThread ourselves.
//----------------------------------------------------------------------

void
LockTest()
{
	printf("Am intrat\n");
    DEBUG('t', "Entering Lock Test");
    Thread *t = new Thread("forked thread");
    t->Fork(SimpleLockThread, 1);
    SimpleLockThread(0);
    lock->Acquire();
    printf("value = %d\n",value);
    lock->Release();
}

