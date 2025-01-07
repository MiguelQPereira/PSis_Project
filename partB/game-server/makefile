# Makefile for game-server

CC = gcc
CFLAGS = -g
LDFLAGS = -lzmq -lncurses
PROTOFLAGS = -lprotobuf-c

all: game-server


game-server: game-server.c ../others/display.c high_score.pb-c.c ../others/structs.h ../others/display.h high_score.pb-c.h
	$(CC) $(CFLAGS) -o game-server game-server.c ../others/display.c high_score.pb-c.c $(LDFLAGS) $(PROTOFLAGS)

#game-server: game-server.o display.o message.o
#	$(CC) $(CFLAGS) -o game-server game-server.o display.o message.o $(LDFLAGS) $(PROTOFLAGS)
#
#game-server.o: game-server.c ../others/structs.h ../others/display.h
#	$(CC) $(CFLAGS) -c game-server.c
#
#display.o: ../others/display.c ../others/structs.h ../others/display.h
#	$(CC) $(CFLAGS) -c ../others/display.c
#
#message.o: message.pb-c.c message.pb-c.h
#	(CC) $(CFLAGS) -c message.pb-c.c 



clean:
	rm -f *.o core game-server *~
