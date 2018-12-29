CXX=g++
CXXFLAGS=-ansi -pedantic -Wall -Werror -I ../Ainclude/ -pthread -g
OBJS=threadpool.o

start: $(OBJS)
	mv $(OBJS) ../Alib/
	make -C ../sync/
	make -C ./test
#	make clean

.PHONY: depends

include depends
depends:
	$(CXX) $(CXXFLAGS) -MM $(OBJS:.o=.cpp)>depends


clean:
	rm $(OBJS)

