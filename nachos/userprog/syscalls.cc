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

void CGYMSyscall::Create(char *name)
{
	DEBUG('s', "Creating file [%s]\n", name);
}

OpenFileId CGYMSyscall::Open(char *name)
{
	DEBUG('s', "Opening file [%s]\n", name);
}

void CGYMSyscall::Write(char *buffer, int size, OpenFileId id)
{
	DEBUG('s', "Writing to file (id=%d,size=%d) [%s]\n", id, size, buffer);
}

int CGYMSyscall::Read(char *buffer, int size, OpenFileId id)
{
	DEBUG('s', "Reading from file (id=%d,size=%d) [%p]\n", id, size, (void *)buffer);
	return 2;
}

void CGYMSyscall::Close(OpenFileId id)
{
	DEBUG('s', "Closing file (id=%d)\n", id);
}
