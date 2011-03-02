include ../Makefile.in

CC = g++

OBJS =  blur.o \
        bokeh.o \
        gamma.o \
        noise.o \
        vignet.o

all: $(OBJS)
%.o: %.cpp $(INCLUDE_DIR)
	$(CC) $(CFLAGS) $(CXXFLAGS) $(COMPILE_FLAGS) -c -o $@ $< $(EXTRA_CFLAGS) $(INCLUDE)

clean:
	rm -f $(EXEC)  *.elf *.gdb *.o *.so.* *.a
