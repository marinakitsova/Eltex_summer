CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lrt -lpthread

all: server client

server: server.c
	gcc -Wall -Wextra -o server server.c -lrt -lpthread

client: client.c
	gcc -Wall -Wextra -o client client.c -lrt -lpthread

clean:
	rm -f server client
