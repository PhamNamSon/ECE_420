CC = gcc
CFLAGS = -Wall

SRCS = server.c client.c

OBJS = $(SRCS:.c=.o)
LIBS = -lpthread -lm

SERVER = main
CLIENT = client
ATTACKER = attacker

all: $(SERVER) $(CLIENT) $(ATTACKER)

$(SERVER): server.o
	$(CC) $(CFLAGS) -o $(SERVER) server.o $(LIBS)

$(CLIENT): client.o
	$(CC) $(CFLAGS) -o $(CLIENT) client.o $(LIBS)

$(ATTACKER): attacker.c
	$(CC) $(CFLAGS) -o $(ATTACKER) attacker.c $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(SERVER) $(CLIENT) $(ATTACKER) server_output_time_aggregated
