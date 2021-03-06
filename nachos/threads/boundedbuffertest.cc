
#include "copyright.h"
#include "system.h"

#define NPRODUCERS 70
#define NCONSUMERS 100

extern void BoundedBuffer(int sz), PutBoundedBuffer(int item);
extern void GetBoundedBuffer(int item);

void
BoundedBufferTest() // function to launch the Producer-Consumer problem
{
    DEBUG('t', "Entering SimpleTest");
    BoundedBuffer(7);
    
    int i;
    for (i=0; i < NPRODUCERS; i++ ){ // create 70 producers
    	char* str = new char[10];
    	sprintf(str,"%d",i);
    	Thread *t = new Thread(str);
    	t->Fork(PutBoundedBuffer, i);
    }
    for ( i=0 ; i< NCONSUMERS ; i++ ){ // and 100 consumers
    	char* str = new char[10];
    	sprintf(str,"%d",i+NPRODUCERS);
    	Thread *t = new Thread(str);
        t->Fork(GetBoundedBuffer, i);
    }
        
}

