/* Header file containing structs, definition of sockets and ip adrress */

int PORT_RR = 5555; // REQ-REP
int PORT_SP = 5554; // SUB-PUB
char IP_ADRESS[16] = "xxx.xxx.xxx.xxx"; //Insert the address

/* ---------------- Structs ---------------- */

// Struct containing the directions to move the astronauts and the aliens
typedef enum directions_t{
    UP,
    DOWN,
    LEFT,
    RIGHT
}directions_;

// Struct containing message type (if the player is joining, moving, etc...), the character the player is going to play adn the directions
typedef struct remote_char_t_{

    int msg_type; // 0 - join  // 1 - move // 2 - zap // 3 - disconnect
    char ch; // character that identifies the client
    directions_ direction;

} remote_char_t;

// Miguel irá comentar
typedef struct server_data_t_{

    char ch;
    int x,y;

} server_data_t;
