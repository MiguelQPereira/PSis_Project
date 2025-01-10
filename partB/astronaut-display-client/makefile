# Makefile for astronaut-display-client

CC = gcc
CFLAGS = -g
LDFLAGS = -pthread -lzmq -lncurses

all: astronaut-display-client

astronaut-display-client: astronaut-display-client.o display.o
	$(CC) $(CFLAGS) -o astronaut-display-client astronaut-display-client.o display.o $(LDFLAGS)

astronaut-display-client.o: astronaut-display-client.c ../others/structs.h ../others/display.h
	$(CC) $(CFLAGS) -c astronaut-display-client.c

display.o: ../others/display.c ../others/structs.h ../others/display.h
	$(CC) $(CFLAGS) -c ../others/display.c

clean:
	rm -f *.o core astronaut-display-client *~