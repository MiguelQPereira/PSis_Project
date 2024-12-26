# Makefile for outer-space-display

CC = gcc
CFLAGS = -g
LDFLAGS = -lzmq -lncurses

all: outer-space-display 

outer-space-display: outer-space-display.o display.o
	$(CC) $(CFLAGS) -o outer-space-display outer-space-display.o display.o $(LDFLAGS)

outer-space-display.o: outer-space-display.c ../others/structs.h ../others/display.h
	$(CC) $(CFLAGS) -c outer-space-display.c

display.o: ../others/display.c ../others/structs.h ../others/display.h
	$(CC) $(CFLAGS) -c ../others/display.c

clean:
	rm -f *.o core outer-space-display *~
