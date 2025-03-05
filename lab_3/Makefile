CC = gcc
CFLAGS = -Wall -fopenmp

TARGET = main
OBJS = main.o Lab3IO.o
DATAGEN = datagen

all: $(TARGET) $(DATAGEN)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(DATAGEN): datagen.o Lab3IO.o
	$(CC) $(CFLAGS) -o $(DATAGEN) datagen.o Lab3IO.o

main.o: main.c timer.h Lab3IO.h
	$(CC) $(CFLAGS) -c main.c

datagen.o: datagen.c Lab3IO.h
	$(CC) $(CFLAGS) -c datagen.c

Lab3IO.o: Lab3IO.c Lab3IO.h
	$(CC) $(CFLAGS) -c Lab3IO.c

clean:
	rm -f $(TARGET) $(DATAGEN) $(OBJS) datagen.o data_input data_output
