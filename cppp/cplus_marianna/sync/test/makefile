CXX=g++ 
CXXFLAGS=-ansi -pedantic -Wall -Werror -I ../../Ainclude/ -pthread -g -D_POSIX_C_SOURCE=199309L
LIB=../../Alib/*.o
OBJS=main.o 

MYEXE=syncTest


$(MYEXE): $(OBJS)  
	$(CXX) $(CXXFLAGS) $(OBJS) $(LIB) -o $(MYEXE) -lrt
#	./$(MYEXE)>test.txt
#	diff results.txt test.txt
	mv $(MYEXE) ../../Abin/
	make clean
	

include depends

.PHONY: clean
depends: 
	$(CXX) $(CXXFLAGS) -MM $(OBJS:.o=.cpp)>depends
	
clean:
	rm $(OBJS)

	

