CXX=g++
CXXFLAGS=-ansi -pedantic -Wall -Werror -I ../Ainclude/ -g
OBJS=timespecExtension.o

start: $(OBJS)
	mv $(OBJS) ../Alib/

.PHONY: depends

include depends
depends:
	$(CXX) $(CXXFLAGS) -MM $(OBJS:.o=.cpp)>depends


clean:
	rm $(OBJS)

