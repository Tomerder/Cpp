CXX=g++ 
CXXFLAGS=-ansi -pedantic -Wall -Werror -I ../../Ainclude/
LIB=../../Alib/*.o

OBJS=main.o

MYEXE=main


$(MYEXE): $(OBJS)  
	$(CXX) $(CXXFLAGS) $(OBJS) $(LIB) -o $(MYEXE)
#	./$(MYEXE)>results.txt
#	diff results.txt CppRes.txt
	mv $(MYEXE) ../../Abin/
	make clean
	

include depends

.PHONY: clean
depends: 
	$(CXX) $(CXXFLAGS) -MM $(OBJS:.o=.cpp)>depends
	
clean:
	rm $(OBJS)

	

