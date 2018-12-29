CC =g++ 
CPPFLAGS = -g -ansi -pedantic -Wall -Werror

EXE = BankTest
OBJS = Bank.o Account.o  Observer.o Subject.o AccImplSaving.o AccImplFamily.o AccImplStock.o BankTest.o AccountImpl.o

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
