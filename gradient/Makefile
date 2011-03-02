include ../Makefile.in

CC = g++

OBJS =  ellipseGradient.o \
        linearGradient.o \
        pointGradient.o 

all: $(OBJS)
%.o: %.cpp $(INCLUDE_DIR)
	$(CC) $(CFLAGS) $(CXXFLAGS) $(COMPILE_FLAGS) -c -o $@ $< $(EXTRA_CFLAGS) $(INCLUDE)

clean:
	rm -f $(EXEC)  *.elf *.gdb *.o *.so.* *.a

