CC = gcc
CFLAGS = -g -Wall
LIBS = -lpthread

obj_files = matrixgen.o lab1_IO.o demo.o
src_files = matrixgen.c lab1_IO.c demo.c

exe_matrixgen = matrixgen
exe_demo = demo

all: $(exe_matrixgen) $(exe_demo)

$(exe_matrixgen): matrixgen.o
	$(CC) $(CFLAGS) -o $@ $^

$(exe_demo): demo.o lab1_IO.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(obj_files) $(exe_matrixgen) $(exe_demo) data_input data_output