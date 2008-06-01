#ifndef FILEDESCRIPTOR_H_
#define FILEDESCRIPTOR_H_

#include "syscall.h"
#include "../filesys/openfile.h"

#define MaxFileNameLength 255

class FileDescriptor
{
public:
	// n-ar trebui sa fie publice, dar...
	char name[MaxFileNameLength];
	OpenFileId fd;
	OpenFile *fp;
	
	FileDescriptor(char *name, OpenFileId fd, OpenFile *fp);
	virtual ~FileDescriptor();
};

#endif /*FILEDESCRIPTOR_H_*/
