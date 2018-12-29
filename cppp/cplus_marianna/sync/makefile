CXX=g++
CXXFLAGS=-ansi -pedantic -Wall -Werror -I ../Ainclude/ -pthread -g  -D_POSIX_C_SOURCE=199309L
OBJS=sync.o 

start: $(OBJS)
	mv $(OBJS) ../Alib/
	make -C ../timespecExtension/
	make -C ./test
#	make clean
	 
.PHONY: depends

include depends
depends:
	$(CXX) $(CXXFLAGS) -MM $(OBJS:.o=.cpp)>depends


clean:
	rm $(OBJS)

