#include "system.h"
#include "syscalls.h"
#include "syscall.h"

CGYMSyscall::CGYMSyscall()
{
}

CGYMSyscall::~CGYMSyscall()
{
}

void CGYMSyscall::Exit(int status)
{
	DEBUG('s', "Exiting with status %d\n", status);
	currentThread->Finish();
}

int CGYMSyscall::Create(char *name)
{
	int rc = -1;
	
	DEBUG('s', "Creating file [%s]\n", name);
	if (fileSystem->Create(name, 0)) {
		rc = 0;
	}
	
	return rc;
}

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

int CGYMSyscall::Write(char *buffer, int size, OpenFileId id)
{
	int rc = -1;
	FileDescriptor *f = currentThread->space->fdTable[id];
	
	DEBUG('s', "Writing to file (id=%d,size=%d) [%s]\n", id, size, buffer);
	if (f != NULL) {
		if (id != 0) {
			if (id == 1) { // scriem la consola
				
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

int CGYMSyscall::Read(char *buffer, int size, OpenFileId id)
{
	int rc = -1;
	FileDescriptor *f = currentThread->space->fdTable[id];
	
	DEBUG('s', "Reading from file (id=%d,size=%d) [%p]\n", id, size, (void *)buffer);
	if (f != NULL) {
		if (id != 1) {
			if (id == 0) { // citim de la consola
				
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
