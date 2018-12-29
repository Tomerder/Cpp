CXX=g++ 
CXXFLAGS=-ansi -pedantic -Wall -Werror -I ../../Ainclude/
LIB=../../Alib/*.o

OBJS=main.o

MYEXE=bitset


$(MYEXE): $(OBJS)  
	$(CXX) $(CXXFLAGS) $(OBJS) $(LIB) -o $(MYEXE)
	./$(MYEXE)>test.txt
#	diff results.txt test.txt
	mv $(MYEXE) ../../Abin/
	make clean
	

include depends

.PHONY: clean
depends: 
	$(CXX) $(CXXFLAGS) -MM $(OBJS:.o=.cpp)>depends
	
clean:
	rm $(OBJS)

	

