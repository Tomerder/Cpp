CC=g++
CPPFLAGS=-ansi -pedantic -Wall -g

test: cpp2c.cpp cpp2c.c
	$(CC) $(CPPFLAGS) cpp2c.cpp -c 
	gcc   $(CPPFLAGS) cpp2c.c   -c
	$(CC) $(CPPFLAGS) cpp2c.cpp -o cppImp
	gcc   $(CPPFLAGS) cpp2c.c   -o cImp
	bash -c "diff <(./cppImp) <(./cImp)"

clean:
	rm *.o cppImp cImp
