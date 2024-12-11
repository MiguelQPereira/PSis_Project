# Makefile for astronaut-client

CC = gcc
CFLAGS = -g
LDFLAGS = -lzmq -lncurses

all: astronaut-client

astronaut-client: astronaut-client.o
	$(CC) $(CFLAGS) -o astronaut-client astronaut-client.o $(LDFLAGS)

astronaut-client.o: astronaut-client.c structs.h
	$(CC) $(CFLAGS) -c astronaut-client.c

clean:
	rm -f *.o core a.out astronaut-client *~
