#Make file do astronaut-client

CC=gcc
CFLAGS= -g -lzmq -lncurses

COR: astronaut-client.o
	$(CC) $(CFLAGS) -o astronaut-client

main.o: main.c comunicacao/TCP.cliente.h comunicacao/TCP.server.h comunicacao/UDP.client.h user_interface.h struct.h
	$(CC) -c $(CFLAGS) main.c

TCP.cliente.o: comunicacao/TCP.cliente.c comunicacao/TCP.cliente.h
	$(CC) -c $(CFLAGS) comunicacao/TCP.cliente.c

TCP.server.o: comunicacao/TCP.server.c comunicacao/TCP.server.h
	$(CC) -c $(CFLAGS) comunicacao/TCP.server.c

UDP.client.o: comunicacao/UDP.client.c comunicacao/UDP.client.h  
	$(CC) -c $(CFLAGS) comunicacao/UDP.client.c

user_interface.o: user_interface.c user_interface.h struct.h
	$(CC) -c $(CFLAGS) user_interface.c

clean::
	rm -f *.o core a.out COR *~