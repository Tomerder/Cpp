CC =g++ 
CPPFLAGS = -g -ansi -pedantic -Wall -Werror

EXE = iConsoleTest
OBJS = iConsoleTest.o MediaPlayer.o PlayerFactory.o  EntConsole.o Memento.o

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@


include depends

depends:
	gcc -MM $(OBJS: .o=.c) > depends


.PHONY: clean todo

clean:
	rm *~ $(EXE) $(OBJS)

todo:
	grep -n TODO *.cpp *.h > todo.txt
	cat todo.txt
