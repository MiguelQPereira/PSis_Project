# Makefile for game-server

CC = gcc
CFLAGS = -g
LDFLAGS = -lzmq -lncurses

all: game-server

game-server: game-server.o display.o
	$(CC) $(CFLAGS) -o game-server game-server.o display.o $(LDFLAGS)

game-server.o: game-server.c display.h
	$(CC) $(CFLAGS) -c game-server.c

display.o: display.c structs.h display.h
	$(CC) $(CFLAGS) -c display.c

clean:
	rm -f *.o core game-server *~
