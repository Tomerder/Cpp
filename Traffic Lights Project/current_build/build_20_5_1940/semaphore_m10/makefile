PROJECT=semaphore_m10
OBJS =$(PROJECT).o
SOURCES = $(OBJS: .o=.cpp)
include ../makefile.common
LDFLAGS +=-Wl,--no-as-needed -pthread -lrt
