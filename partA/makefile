
all: game-server astronaut-client outer-space-display display

game-server: game-server.c display.h structs.h
	gcc -o game-server game-server.c display.c -g -lzmq -lncurses

astronaut-client: astronaut-client.c structs.h
	gcc -o astronaut-client astronaut-client.c -g -lzmq -lncurses

outer-space-display: outer-space-display.c structs.h display.h
	gcc -o outer-space-display outer-space-display.c display.c -g -lzmq -lncurses

display: display.c structs.h
	gcc -o display display.c -g -lzmq -lncurses

clean:
	rm -f game-server astronaut-client outer-space-display