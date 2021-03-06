# use normal make for this Makefile
#
# Makefile for building user programs to run on top of Nachos
#
# Several things to be aware of:
#
#    Nachos assumes that the location of the program startup routine (the
# 	location the kernel jumps to when the program initially starts up)
#       is at location 0.  This means: start.o must be the first .o passed 
# 	to ld, in order for the routine "Start" to be loaded at location 0
#

# if you are cross-compiling, you need to point to the right executables
# and change the flags to ld and the build procedure for as
# GCCDIR = ~/gnu/local/decstation-ultrix/bin/
# LDFLAGS = -T script -N
# ASFLAGS = -mips
# CPPFLAGS = $(INCDIR)


# if you aren't cross-compiling:
GCCDIR = /usr/local/mips/bin/
LDFLAGS = -N -T script
ASFLAGS =
CPPFLAGS = -P $(INCDIR)


CC = $(GCCDIR)mips-gcc
AS = $(GCCDIR)mips-as
LD = $(GCCDIR)mips-ld

#CPP = /lib/cpp
CPP = /usr/local/mips/bin/cpp
INCDIR =-I../userprog -I../threads
CFLAGS = -G 0 -c $(INCDIR)

all: halt matmult shell sort test shell2

start.o: start.s ../userprog/syscall.h
	$(CPP) $(CPPFLAGS) start.s > strt.s
	$(AS) $(ASFLAGS) -o start.o strt.s
	rm strt.s

halt.o: halt.c
	$(CC) $(CFLAGS) -c halt.c
halt: halt.o start.o
	$(LD) $(LDFLAGS) start.o halt.o -o halt.coff
	../bin/coff2noff halt.coff halt

shell.o: shell.c
	$(CC) $(CFLAGS) -c shell.c
shell: shell.o start.o
	$(LD) $(LDFLAGS) start.o shell.o -o shell.coff
	../bin/coff2noff shell.coff shell

sort.o: sort.c
	$(CC) $(CFLAGS) -c sort.c
sort: sort.o start.o
	$(LD) $(LDFLAGS) start.o sort.o -o sort.coff
	../bin/coff2noff sort.coff sort

matmult.o: matmult.c
	$(CC) $(CFLAGS) -c matmult.c
matmult: matmult.o start.o
	$(LD) $(LDFLAGS) start.o matmult.o -o matmult.coff
	../bin/coff2noff matmult.coff matmult

test.o: test.c
	$(CC) $(CFLAGS) -c test.c
test: test.o start.o
	$(LD) $(LDFLAGS) start.o test.o -o test.coff
	../bin/coff2noff test.coff test

shell2.o: shell2.c
	$(CC) $(CFLAGS) -c shell2.c
shell2: shell2.o start.o
	$(LD) $(LDFLAGS) start.o shell2.o -o shell2.coff
	../bin/coff2noff shell2.coff shell2
