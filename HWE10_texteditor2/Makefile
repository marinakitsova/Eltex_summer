CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LIBS = -lncurses

OBJS = file_manager.o

all: file_manager

file_manager: file_manager.o
	    gcc -o file_manager file_manager.o -lncurses

file_manager.o: file_manager.c file_manager.h
	    gcc -Wall -Wextra -std=c99 -c file_manager.c -o file_manager.o

clean:
	    rm -f file_manager file_manager.o
