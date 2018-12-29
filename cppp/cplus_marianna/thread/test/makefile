CXX=g++ 
CXXFLAGS=-ansi -pedantic -Wall -Werror -I ../../Ainclude/ -pthread -g
OBJS=main.o 

MYEXE=threadTest


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

	

