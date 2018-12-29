LIB_NAME := traffic

PROJ_DIRS := state_machine hardware config tcp_ip semaphore_m10 thread mutex timing priorityqueue log comm display


HEADER_PATH += ./Ainclude
LIB_PATH := ./Alib
BIN_PATH := ./Abin


TARGET = $(if $(MAKECMDGOALS), $(firstword $(MAKECMDGOALS)), objs)


.PHONY: clean objs commit $(PROJ_DIRS)


all: $(PROJ_DIRS)
	$(if $(TARGET), $(MAKE) $(TARGET))

commit: $(PROJ_DIRS)
	gcc -shared  -o $(LIB_PATH)/lib$(LIB_NAME).so -Wl,--whole-archive $(LIB_PATH)/lib$(LIB_NAME).a -Wl,--no-whole-archive

#./ALIB: $(PROJ_DIRS)

$(PROJ_DIRS):
	$(MAKE) --directory=$@ $(TARGET)


test: $(PROJ_DIRS)

clean: $(PROJ_DIRS)
	-rm $(LIB_PATH)/*
	-rm $(BIN_PATH)/*.*
	-rm $(BIN_PATH)/tests/*.*
