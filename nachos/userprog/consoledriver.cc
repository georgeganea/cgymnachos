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
	readAvail->P(); // wait until we can read something
	return console->GetChar(); // return the read character
}

void ConsoleDriver::putchar(char ch)
{
	console->PutChar(ch); // write the character
	writeDone->P(); // wait for the write to finish
}

/* Reads a string from the console up to len-1 bytes long,
 * or up to the new line character, which ever comes first.
 * Appends the null terminator character.
 */
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

/* Prints out the string in buf */
void ConsoleDriver::puts(char *buf)
{
	while (*buf != '\0') putchar(*buf++);
}

/* Callback argument for the Console class.
 * Will be called when there is data waiting to be read.
 */
void ConsoleDriver::ReadAvail(int callArg)
{
	readAvail->V();
}

/* Callback argument for the Console class.
 * Will be called when a writing operation has finished.
 */
void ConsoleDriver::WriteDone(int callArg)
{
	writeDone->V();
}
