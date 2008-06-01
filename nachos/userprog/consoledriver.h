#ifndef CONSOLEDRIVER_H_
#define CONSOLEDRIVER_H_

#include "console.h"
#include "synch.h"

class ConsoleDriver
{
public:
	ConsoleDriver();
	virtual ~ConsoleDriver();
	char getchar();
	void putchar(char ch);
	int gets(char *buf, int len);
	void puts(char *buf);
private:
	static Console *console;
	static Semaphore *readAvail;
	static Semaphore *writeDone;
	static void ReadAvail(int callArg);
	static void WriteDone(int callArg);
};

#endif /*CONSOLEDRIVER_H_*/
