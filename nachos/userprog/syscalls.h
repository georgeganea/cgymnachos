#ifndef SYSCALLS_H_
#define SYSCALLS_H_

#include "syscall.h"

class CGYMSyscall
{
public:
	CGYMSyscall();
	virtual ~CGYMSyscall();

	/* This user program is done (status = 0 means exited normally). */
	static void Exit(int status);	
	 	 

	/* File system operations: Create, Open, Read, Write, Close
	 * These functions are patterned after UNIX -- files represent
	 * both files *and* hardware I/O devices.
	 *
	 * If this assignment is done before doing the file system assignment,
	 * note that the Nachos file system has a stub implementation, which
	 * will work for the purposes of testing out these routines.
	 */
	 
	/* A unique identifier for an open Nachos file. */
	typedef int OpenFileId;	
	 
	/* Create a Nachos file, with "name" */
	static int Create(char *name);

	/* Open the Nachos file "name", and return an "OpenFileId" that can 
	 * be used to read and write to the file.
	 */
	static OpenFileId Open(char *name);

	/* Write "size" bytes from "buffer" to the open file. */
	static int Write(char *buffer, int size, OpenFileId id);

	/* Read "size" bytes from the open file into "buffer".  
	 * Return the number of bytes actually read -- if the open file isn't
	 * long enough, or if it is an I/O device, and there aren't enough 
	 * characters to read, return whatever is available (for I/O devices, 
	 * you should always wait until you can return at least one character).
	 */
	static int Read(char *buffer, int size, OpenFileId id);

	/* Close the file, we're done reading and writing to it. */
	static int Close(OpenFileId id);
};

#endif /*SYSCALLS_H_*/
