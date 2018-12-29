SUBDIRS = bitSet mystring complex globaliniter mutex mytime priorityqueue semaphoremy singleton thread threadpool
DIR = ./Alib/

.PHONY: all
all:
	for dir in $(SUBDIRS); do \
	$(MAKE) -C $$dir; \
	done

.PHONY: clean
clean:
	rm $(DIR)libmy.a
	rm $(DIR)libmy.so
	for dir in $(SUBDIRS); do \
	$(MAKE) clean -C $$dir; \
	done

commit:
	for dir in $(SUBDIRS); do \
	$(MAKE) commit -C $$dir; \
	done
	g++ -shared -o $(DIR)libmy.so -Wl,--whole-archive $(DIR)libmy.a -Wl,--no-whole-archive
	
test:
	for dir in $(SUBDIRS) ; do \
	$(MAKE) test -C $$dir; \
	done



#SUBDIRS = bitSet/test mystring/test complex/test globaliniter/test mutex/test mytime/test priorityqueue/test semaphoremy/test singleton/test thread/test threadpool/test
