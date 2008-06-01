#include "filedescriptor.h"

/* Aceasta clasa este de fapt o strutura de date
 * pentru informatiile unui file descriptor.
 */

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
