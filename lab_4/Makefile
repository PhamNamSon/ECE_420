# Compiler and flags
MPICC = mpicc
CC = gcc
CFLAGS = -Wall -lm

# Targets
TARGET_MAIN = main
TARGET_DATATRIM = datatrim

# Source files
MAIN_SRC = main.c Lab4_IO.c
DATATRIM_SRC = datatrim.c

# Header dependencies
HEADERS = Lab4_IO.h timer.h

# Default build target
all: $(TARGET_MAIN) $(TARGET_DATATRIM)

# Build the MPI program
$(TARGET_MAIN): $(MAIN_SRC) $(HEADERS)
	$(MPICC) $(MAIN_SRC) -o $(TARGET_MAIN) $(CFLAGS)

# Build the datatrim utility
$(TARGET_DATATRIM): $(DATATRIM_SRC)
	$(CC) $(DATATRIM_SRC) -o $(TARGET_DATATRIM) $(CFLAGS)

# Clean up build files
clean:
	rm -f $(TARGET_MAIN) $(TARGET_DATATRIM) \
	      data_input_link data_input_meta data_output
