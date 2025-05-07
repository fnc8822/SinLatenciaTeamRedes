CC = gcc
CFLAGS = -Wall -pthread
RM = rm -f

all: server client

server: server.c
	$(CC) $(CFLAGS) -o server server.c

client: client.c
	$(CC) $(CFLAGS) -o client client.c

clean:
	$(RM) server client