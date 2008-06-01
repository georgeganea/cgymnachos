#include "system.h"
#include "syscalls.h"
#include "syscall.h"

CGYMSyscall::CGYMSyscall()
{
}

CGYMSyscall::~CGYMSyscall()
{
}

/* Terminates the calling thread normally.
 * The program terminates with the given exit code.
 */
void CGYMSyscall::Exit(int status)
{
	DEBUG('s', "Exiting with status %d\n", status);
	currentThread->Finish();
}

/* Creates a file with the given name.
 * 
 * Returns:
 * 0	on success
 * -1	on error
 */
int CGYMSyscall::Create(char *name)
{
	int rc = -1;
	
	DEBUG('s', "Creating file [%s]\n", name);
	if (fileSystem->Create(name, 0)) {
		rc = 0;
	}
	
	return rc;
}

/* Opens the file with the given name.
 * Returns:
 * 
 * -1	on error
 * fd	on success
 */ 
OpenFileId CGYMSyscall::Open(char *name)
{
	OpenFileId rc = -1;
	DEBUG('s', "Opening file [%s]\n", name);
	OpenFile *fp = fileSystem->Open(name);
		
	if (fp != NULL) {
		rc = (currentThread->space)->createFD(name, fp);
		DEBUG('s', "newfd = %d\n", rc);
	} else {
		DEBUG('s', "open failed.\n");
	}
	
	return rc;
}

/* Write size bytes, starting at location buffer to
 * the id file descriptor.
 * Uses the console driver is id is stdout (1).
 * 
 * Returns:
 * number of written bytes on success
 * -1 on error
 */
int CGYMSyscall::Write(char *buffer, int size, OpenFileId id)
{
	int rc = -1, i;
	FileDescriptor *f = currentThread->space->fdTable[id];
	
	DEBUG('s', "Writing to file (id=%d,size=%d) [%s]\n", id, size, buffer);
	if (f != NULL) {
		if (id != ConsoleInput) {
			if (id == ConsoleOutput) { // scriem la consola
				for (i = 0; i < size; i++)
					consoleDriver->putchar(buffer[i]);
				rc = i;
			} else { // scriem in fisier
				rc = f->fp->Write(buffer, size);
			}
		} else {
			// eroare -- nu putem scrie in stdin
		}
	} else {
		// eroare -- nu e bun fd-ul
	}
	
	return rc;
}

/* Reads size bytes from the given file descriptor
 * into buffer.
 * 
 * Returns:
 * the number of read bytes on success
 * -1 on error
 */
int CGYMSyscall::Read(char *buffer, int size, OpenFileId id)
{
	int rc = -1;
	FileDescriptor *f = currentThread->space->fdTable[id];
	
	DEBUG('s', "Reading from file (id=%d,size=%d) [%p]\n", id, size, (void *)buffer);
	if (f != NULL) {
		if (id != ConsoleOutput) {
			if (id == ConsoleInput) { // citim de la consola
				rc = consoleDriver->gets(buffer, size);
			} else { // citim din fisier
				rc = f->fp->Read(buffer, size);
			}
		} else {
			// eroare -- nu putem citi din stdout
		}
	} else {
		// eroare -- nu e bun fd-ul
	}
	
	return rc;
}

/*
 * Close an open file descriptor.
 * Returns
 * 0	on success
 * -1	on error
 */
int CGYMSyscall::Close(OpenFileId id)
{
	int rc = -1;
	
	DEBUG('s', "Closing file (id=%d)\n", id);
	if ((currentThread->space)->freeFD(id) != 0) {
		DEBUG('s', "error closing file\n");
	} else {
		rc = 0;
	}
	
	return rc;
}

/* Suspends thread execution for the given number of ticks. */
void CGYMSyscall::Sleep(int ticks)
{
	DEBUG('s', "Going to sleep (for %d ticks)\n", ticks);
	timerDriver->addTimer(currentThread, ticks);
	
	IntStatus oldValue = interrupt->SetLevel(IntOff); // disable interrupts
	currentThread->Sleep();
	interrupt->SetLevel(oldValue); // restore interrupts
}
