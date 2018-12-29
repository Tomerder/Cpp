PROJECT=thread
OBJS =$(PROJECT).o
SOURCES = $(OBJS: .o=.cpp)
include ../makefile.common
LDFLAGS +=-Wl,--no-as-needed -pthread -lrt
