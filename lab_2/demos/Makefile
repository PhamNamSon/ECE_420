# Makefile for compiling arrayRW.c

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -pthread

# Source files
SRC = arrayRW.c

# Object files
OBJ = $(SRC:.c=.o)

# Executable name
EXE = arrayRW

# Common header file (assuming it exists)
COMMON_HEADERS = common.h

# Rule to compile
all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)

%.o: %.c $(COMMON_HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean
clean:
	rm -f $(OBJ) $(EXE)

# Rule to run the program with a specified number of threads
run: $(EXE)
	./$(EXE) 4  # Change 4 to the desired number of threads
