#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <zmq.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

#ifndef STRUCTS_H
#define STRUCTS_H
#define  WINDOW_SIZE 20
#define N_ALIENS 85



/* Header file containing structs, definition of sockets and ip adrress */

#define PORT_RR  5555 // REQ-REP
#define PORT_SP  5554 // SUB-PUB
#define IP_ADRESS  "192.168.1.87" //Insert the address



/* ------------------------------------------------------------------------- */
/* -------------------------------- Structs -------------------------------- */
/* ------------------------------------------------------------------------- */


// Struct containing the directions to move the astronauts and the aliens
typedef enum directions_t{
    UP,
    DOWN,
    LEFT,
    RIGHT
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
    time_t stun;  // Beguining of the stun
    time_t last_zap;  // Time of the last zap shot
    int x,y; // position of the caracter

} player_data_t;


// Struct containing the relevant information of a alien
typedef struct alien_data_t_ {

    int x,y; // Positions of the aliens
    int hp; // 0 -> Dead // 1 -> Alive

}alien_data_t;


// Struct that connects a zap in space to the player that shoot it
typedef struct pewpew_t_ {
    time_t time;        // Moment the zap message was received
    int player;         // Player that shot the zap
}pewpew_t;

#endif //STRUCTS_H
