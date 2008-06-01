
#include "copyright.h"
#include "system.h"
#include "synch.h"

// ---- Class for buffer of fixed size, with synchronization ---------

// This version uses mutex locks and condition variables to perform 
//   the needed synchronization.

  int* buffer;
  unsigned int bufferSize;
  unsigned int nextToRemove;
  unsigned int numElements;
  // Variables for synchronization:
  Lock* bufferLock;	 // lock for shared variables
  Condition* bufferNotEmpty; // get() waits on this condition 
				 // variable if buffer is empty
  Condition* bufferNotFull;	 // put() waits on this condition
  				// variable if buffer is full

  
void BoundedBuffer(const int sz) {// init function - creates everything we need to launch the consumers and the producers
    bufferSize = sz;
    buffer = new int[sz];
    nextToRemove = 0;
    numElements = 0;
    bufferLock = new Lock((char *)"buffer lock");
    bufferNotEmpty = new Condition((char *)"buffer not empty");
    bufferNotFull = new Condition((char *)"buffer not full");
    printf("\n a fost apelata !!\n ");
    
  }

 

  // Put "item" into buffer, with appropriate synchronization.
  void PutBoundedBuffer(const int item) { // producer thread
	  printf("in put\n");
    bufferLock->Acquire();
    if (numElements == bufferSize) // buffer full
      bufferNotFull->Wait(bufferLock); // wait for some room in the buffer
    unsigned int next = (nextToRemove + numElements) % bufferSize;// calculate "put" position
    buffer[next] = item; // producers insert in one end, consumers extract from the other
    printf("am pus %d\n",item);
    ++numElements;
    bufferNotEmpty->Signal(bufferLock);
    bufferLock->Release();
    currentThread->Yield();
  }

  // Get item from buffer, with appropriate synchronization.
  void GetBoundedBuffer(int i) {//consumer thread
	  printf("in get\n");
    bufferLock->Acquire();
    if (numElements == 0)//if nothing to consume
      bufferNotEmpty->Wait(bufferLock);// wait for some "products" in the buffer
    int returnVal = buffer[nextToRemove]; // consume it
    printf("am scos %d\n",returnVal);
    nextToRemove = (nextToRemove + 1) % bufferSize;
    --numElements;
    bufferNotFull->Signal(bufferLock);
    bufferLock->Release();//release the lock
    currentThread->Yield();
  }


