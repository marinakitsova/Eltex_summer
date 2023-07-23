CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lrt -lpthread

all: server client

server: server.c
		$(CC) $(CFLAGS) -o server server.c $(LDFLAGS)

client: client.c
		$(CC) $(CFLAGS) -o client client.c $(LDFLAGS)

.PHONY: clean

clean:
		rm -f server client
