// addrspace.h 
//	Data structures to keep track of executing user programs 
//	(address spaces).
//
//	For now, we don't keep any information about address spaces.
//	The user level CPU state is saved and restored in the thread
//	executing the user program (see thread.h).
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#ifndef ADDRSPACE_H
#define ADDRSPACE_H

#include "copyright.h"
#include "filesys.h"
#include "filedescriptor.h"
#include "syscall.h"

#define UserStackSize		1024 	// increase this as necessary!
#define MaxFDCount			8		// maximum open file descriptors per process

class AddrSpace {
  public:
    AddrSpace(OpenFile *executable);	// Create an address space,
					// initializing it with the program
					// stored in the file "executable"
    ~AddrSpace();			// De-allocate an address space

    void InitRegisters();		// Initialize user-level CPU registers,
					// before jumping to user code

    void SaveState();			// Save/restore address space-specific
    void RestoreState();		// info on a context switch

    /* Added functions and data structures for file descriptors */
    FileDescriptor *fdTable[MaxFDCount];	// open file descriptor table
    
    OpenFileId createFD(char *name, OpenFile *fp);
    int freeFD(OpenFileId fd);
    void freeFDTable();

  private:
    TranslationEntry *pageTable;	// Assume linear page table translation
					// for now!
    unsigned int numPages;		// Number of pages in the virtual 
					// address space
    
    /* Internal file descriptor functions */
    int getFreeFDPos();
    int getFDByFileName(char *name);
    void dumpFD();
};

#endif
