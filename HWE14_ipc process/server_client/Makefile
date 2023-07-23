CC = gcc
CFLAGS = -Wall

all: server_systemv client_systemv

server_systemv: server_systemv.c
		$(CC) $(CFLAGS) -o server_systemv server_systemv.c

client_systemv: client_systemv.c
		$(CC) $(CFLAGS) -o client_systemv client_systemv.c

clean:
		rm -f server_systemv client_systemv
