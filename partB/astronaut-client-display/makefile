# Makefile for astronaut-client-display

CC = gcc
CFLAGS = -g
LDFLAGS = -pthread -lzmq -lncurses

all: astronaut-client-display

astronaut-client-display: astronaut-client-display.o display.o
	$(CC) $(CFLAGS) -o astronaut-client-display astronaut-client-display.o display.o $(LDFLAGS)

astronaut-client-display.o: astronaut-client-display.c ../others/structs.h ../others/display.h
	$(CC) $(CFLAGS) -c astronaut-client-display.c

display.o: ../others/display.c ../others/structs.h ../others/display.h
	$(CC) $(CFLAGS) -c ../others/display.c

clean:
	rm -f *.o core astronaut-client-display *~