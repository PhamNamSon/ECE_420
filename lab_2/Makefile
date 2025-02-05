CC = gcc
CFLAGS = -Wall

SRCS = server.c client.c

OBJS = $(SRCS:.c=.o)
LIBS = -lpthread

SERVER = main
CLIENT = client

all: $(SERVER) $(CLIENT)

$(SERVER): server.o
	$(CC) $(CFLAGS) -o $(SERVER) server.o $(LIBS)

$(CLIENT): client.o
	$(CC) $(CFLAGS) -o $(CLIENT) client.o $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(SERVER) $(CLIENT)
