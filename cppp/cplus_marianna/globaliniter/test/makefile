CXX=g++ 
CXXFLAGS=-ansi -pedantic -Wall -Werror -I ../../Ainclude/

OBJS=main.o globals.o

MYEXE=globalIniter


$(MYEXE): $(OBJS)  
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(MYEXE)
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

	

