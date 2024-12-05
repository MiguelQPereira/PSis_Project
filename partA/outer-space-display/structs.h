#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <zmq.h>


#define  WINDOW_SIZE 20

/* Header file containing structs, definition of sockets and ip adrress */

int PORT_RR = 5555; // REQ-REP
int PORT_SP = 5554; // SUB-PUB
char IP_ADRESS[16] = "192.168.1.70"; //Insert the address



/* ------------------------------------------------------------------------- */
/* -------------------------------- Structs -------------------------------- */
/* ------------------------------------------------------------------------- */


// Struct containing the directions to move the astronauts and the aliens
typedef enum directions_t{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ZAP,
    QUIT
}directions_;

// Struct containing message type (if the player is joining, moving, etc...), the character the player is going to play, the directions and ID
typedef struct remote_char_t_{
    int id; // personal identifier of the client
    int msg_type; // 0 - join  // 1 - move // 2 - zap // 3 - disconnect
    char ch; // character that identifies the client
    directions_ direction; // directions of the character

} remote_char_t;

// Struct containing the relevant information of a player
typedef struct player_data_t_{
    int id; // personal identifier given by server at run time to a client
    char ch; // caracter that the player controls
    int score; // Saves the players scores 
    int x,y; // position of the caracter

} player_data_t;


// Struct containing the relevant information of a alien
typedef struct alien_data_t_ {

    int x,y; // Positions of the aliens
    int hp; // 0 -> Dead // 1 -> Alive

}alien_data_t;

