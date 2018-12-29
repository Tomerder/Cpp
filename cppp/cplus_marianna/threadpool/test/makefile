CXX=g++ 
CXXFLAGS=-ansi -pedantic -Wall -Werror -I ../../Ainclude/ -pthread -g
LIB=../../Alib/*.o
OBJS=main.o 

MYEXE=threadPoolBarbaricTest


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

	

