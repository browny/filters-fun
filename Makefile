include Makefile.in

SHELL = /bin/sh
CC = g++
OBJS = fileReader.o \
	controller.o \
	filterBank.o \
	utility.o 

EXEC = main
DIR_FILTER = filter
DIR_GRADIENT = gradient
DIR_WINDOW = window
SUBDIRS = $(DIR_FILTER) $(DIR_GRADIENT) $(DIR_WINDOW)
ALL_OBJS = `find ./ -name '*.o'`

all: subdir $(OBJS)
	$(CC) $(EXEC).cpp -o $(EXEC) $(ALL_OBJS) $(INCLUDE) $(COMPILE_FLAGS)

subdir: 
	for i in $(SUBDIRS); do (cd $$i && make all); done

%.o: %.cpp 
	$(CC) $(CFLAGS) $(CXXFLAGS) $(COMPILE_FLAG) -c -o $@ $< $(EXTRA_CFLAGS) $(INCLUDE) $(COMPILE_FLAGS)

clean:
	rm -f $(EXEC) $(ALL_OBJS) *.elf *.gdb *.so.* *.a
