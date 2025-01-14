CC = gcc
CFLAGS = -g -Wall
LIBS = -lpthread

obj_files = matrixgen.o lab1_IO.o main.o
src_files = matrixgen.c lab1_IO.c main.c

exe_matrixgen = matrixgen
exe_main = main

all: $(exe_matrixgen) $(exe_main)

$(exe_matrixgen): matrixgen.o
	$(CC) $(CFLAGS) -o $@ $^

$(exe_main): main.o lab1_IO.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(obj_files) $(exe_matrixgen) $(exe_main) data_input data_output