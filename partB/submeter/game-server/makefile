# Makefile for game-server

CC = gcc
CFLAGS = -g
LDFLAGS = -lzmq -lncurses
PROTOFLAGS = -lprotobuf-c

all: game-server


game-server: game-server.c ../others/display.c high_score.pb-c.c ../others/structs.h ../others/display.h high_score.pb-c.h
	$(CC) $(CFLAGS) -o game-server game-server.c ../others/display.c high_score.pb-c.c $(LDFLAGS) $(PROTOFLAGS)

clean:
	rm -f *.o core game-server *~
