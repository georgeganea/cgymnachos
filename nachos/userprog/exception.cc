// exception.cc 
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.  
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"
#include "syscalls.h"

char *GetSyscallParam(int reg);

//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//	"which" is the kind of exception.  The list of possible exceptions 
//	are in machine.h.
//----------------------------------------------------------------------

void
ExceptionHandler(ExceptionType which)
{
    int type = machine->ReadRegister(2);

    if (which == SyscallException) {
    	// Added support for all implemented syscalls
    	
    	/*
    	int val = machine->ReadRegister(4), c;
 
    	DEBUG('a', "value=%d\n", val); 	
    	machine->Translate(val, &c, 1, FALSE);
       	DEBUG('a', "string = [%s]\n", (char *)&(machine->mainMemory[c]));
       	*/
    	
    	if (type == SC_Halt) {
    		DEBUG('a', "Shutdown, initiated by user program.\n");
    		interrupt->Halt();
    	} else if (type == SC_Exit) {
    		DEBUG('a', "Exit() called.\n");
    		CGYMSyscall::Exit( machine->ReadRegister(4) );
    	} else if (type == SC_Open) {
    		DEBUG('a', "Open() called.\n");
    		OpenFileId id = CGYMSyscall::Open( GetSyscallParam(4) );
    		machine->WriteRegister(2, id);
    	} else if (type == SC_Close) {
    		DEBUG('a', "Close() called.\n");
    		machine->WriteRegister(2,
    				CGYMSyscall::Close( machine->ReadRegister(4) ));
    	} else if (type == SC_Read) {
    		DEBUG('a', "Read() called.\n");
    		machine->WriteRegister(2,
    				CGYMSyscall::Read(GetSyscallParam(4),
    				    				machine->ReadRegister(5), machine->ReadRegister(6)));
    	} else if (type == SC_Write) {
    		DEBUG('a', "Write() called.\n");
    		machine->WriteRegister(2,
    				CGYMSyscall::Write(GetSyscallParam(4),
    						machine->ReadRegister(5), machine->ReadRegister(6)));
    	} else if (type == SC_Create) {
    		DEBUG('a', "Create() called.\n");
    		machine->WriteRegister(2,
    				CGYMSyscall::Create( GetSyscallParam(4) ));
    	} else if (type == SC_Sleep) {
    		DEBUG('a', "Sleep() called.\n");
    		CGYMSyscall::Sleep( machine->ReadRegister(4) );
    	}
    	
    	/* Advance the PC and the other PC related registers
    	 * before returning from the syscall 
    	 */
    	int pc = machine->ReadRegister(PCReg);
    	machine->WriteRegister(PrevPCReg, pc);
    	pc = machine->ReadRegister(NextPCReg);
    	machine->WriteRegister(PCReg, pc);
    	pc += 4;
    	machine->WriteRegister(NextPCReg, pc);
    } else {
    	printf("Unexpected user mode exception %d %d\n", which, type);
    	ASSERT(FALSE);
    }
}

/*
 * This method returns the physical address from the user space address,
 * given in register reg.
 */
char *GetSyscallParam(int reg)
{
	int virt = machine->ReadRegister(reg), phys;
	char *rc = NULL;
	
	if (NoException == machine->Translate(virt, &phys, 1, FALSE)) {
		rc = (char *)&(machine->mainMemory[phys]);
	}
	
	return rc;
}
