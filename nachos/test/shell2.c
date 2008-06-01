#include "syscall.h"

#define READ_MSG "Am citit: "

int strcmp(char *s, char *t) {
	while (*s != '\0' && *t != '\0' && *s++ == *t++);
	
	return (*s == *t);
}

int strlen(char *s) {
	int len = 0;
	
	while (*s++ != '\0') len++;
	
	return len;
}

int
main()
{
    OpenFileId input = ConsoleInput;
    OpenFileId output = ConsoleOutput;
    char prompt[2], ch, buffer[60];
    int i;

    prompt[0] = '-';
    prompt[1] = '-';

    while( 1 )
    {
    	Write(prompt, 2, output);

    	i = Read(buffer, 60, input);

    	if( i > 0 ) {
    		Write(READ_MSG, strlen(READ_MSG), output);
    		Write(buffer, strlen(buffer), output);
    	}
    }
}
