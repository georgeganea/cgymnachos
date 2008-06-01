#include "filedescriptor.h"

FileDescriptor::FileDescriptor(char *name, OpenFileId fd, OpenFile *fp)
{
	strcpy(this->name, name);
	this->fd = fd;
	this->fp = fp;
}

FileDescriptor::~FileDescriptor()
{
	fd = -1;
	*name = '\0';
	fp = NULL;
}
