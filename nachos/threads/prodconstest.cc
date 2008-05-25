
#include "copyright.h"
#include "system.h"

#define NPRODUCERS 10
#define NCONSUMERS 10

extern void BoundedBuffer(int sz), PutBoundedBuffer(int item);
extern void GetBoundedBuffer(int item);
char str[10];
void
BoundedBufferTest()
{
    DEBUG('t', "Entering SimpleTest");
    BoundedBuffer(7);
    
    int i;
    for (i=0; i < 10; i++ ){
    	sprintf(str,"%d\0",i);
    	Thread *t = new Thread(str);
    t->Fork(PutBoundedBuffer, i);
    }
    for ( i=0 ; i< 10 ; i++ ){
    	sprintf(str,"%d\0",i+10);
    	Thread *t = new Thread(str);
        t->Fork(GetBoundedBuffer, i);
    }
        
}

