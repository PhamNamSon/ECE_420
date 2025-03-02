CC = gcc
CFLAGS = -fopenmp
SRCS = main.c Lab3IO.c
OBJS = main

all: $(OBJS)

$(OBJS): $(SRCS)
	$(CC) $(SRCS) -o $(OBJS) $(CFLAGS)

clean:
	rm -f $(OBJS)
