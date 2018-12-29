CC=gcc
CFLAGS=-ansi -pedantic -Wall -g

COBJS=ccode_main.o ccode.o


all: orig ccode

orig: orig.cpp
	g++ $(CFLAGS) $^ -o $@

ccode: $(COBJS)
	$(CC) $^ -o $@


include depends
depends:
	$(CC) $(CFLAGS) -MM $(COBJS:.o=.c) > depends


clean:
	rm *.o

