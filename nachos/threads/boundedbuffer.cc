
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

  
void BoundedBuffer(const int sz) {
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
  void PutBoundedBuffer(const int item) {
	  printf("in put\n");
    bufferLock->Acquire();
    if (numElements == bufferSize)
      bufferNotFull->Wait(bufferLock);
    unsigned int next = (nextToRemove + numElements) % bufferSize;
    buffer[next] = item;
    printf("am pus %d\n",item);
    ++numElements;
    bufferNotEmpty->Signal(bufferLock);
    bufferLock->Release();
    currentThread->Yield();
  }

  // Get item from buffer, with appropriate synchronization.
  void GetBoundedBuffer(int i) {
	  printf("in get\n");
    bufferLock->Acquire();
    if (numElements == 0)
      bufferNotEmpty->Wait(bufferLock);
    int returnVal = buffer[nextToRemove];
    printf("am scos %d\n",returnVal);
    nextToRemove = (nextToRemove + 1) % bufferSize;
    --numElements;
    bufferNotFull->Signal(bufferLock);
    bufferLock->Release();
    currentThread->Yield();
  }


