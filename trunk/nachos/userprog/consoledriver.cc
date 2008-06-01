#include "consoledriver.h"

Console *ConsoleDriver::console;
Semaphore *ConsoleDriver::readAvail;
Semaphore *ConsoleDriver::writeDone;

ConsoleDriver::ConsoleDriver()
{
	readAvail = new Semaphore("readAvail", 0);
	writeDone = new Semaphore("writeDone", 0);
	console = new Console(NULL, NULL, ReadAvail, WriteDone, 0);
}

ConsoleDriver::~ConsoleDriver()
{
	delete console;
	delete readAvail;
	delete writeDone;
}

char ConsoleDriver::getchar()
{
	readAvail->P();
	return console->GetChar();
}

void ConsoleDriver::putchar(char ch)
{
	console->PutChar(ch);
	writeDone->P();
}

int ConsoleDriver::gets(char *buf, int len)
{
	int pos = 0;
	
	while (pos < len - 1) {
		buf[pos] = getchar();
		if (buf[pos++] == '\n') break;
	}
	
	buf[pos] = '\0';
	
	return pos;
}

void ConsoleDriver::puts(char *buf)
{
	while (*buf != '\0') putchar(*buf++);
}

void ConsoleDriver::ReadAvail(int callArg)
{
	readAvail->V();
}

void ConsoleDriver::WriteDone(int callArg)
{
	writeDone->V();
}
