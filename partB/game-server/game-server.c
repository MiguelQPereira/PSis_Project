#include "../others/display.h"

// Sends the messages to the outer-space display with the information to print
void outer_space_update(void *socket, player_data_t players[8], alien_data_t aliens[N_ALIENS], pewpew_t zaps[2][16], time_t time, int game) {
    
    int rc;
        rc = zmq_send (socket, "DISPLAY", strlen("DISPLAY"), ZMQ_SNDMORE);  // Type
        if (rc == -1){
            mvprintw(0,0,"--- ERROR ---\nFAILED TO PUBLISH MESSAGE 1");
            exit(0);
        }

        rc = zmq_send (socket, players, sizeof(player_data_t)*8, ZMQ_SNDMORE);  // Player data
        if (rc == -1){
            mvprintw(0,0,"--- ERROR ---\nFAILED TO PUBLISH MESSAGE 2");
            exit(0);
        }

        rc = zmq_send (socket, aliens, sizeof(alien_data_t)*N_ALIENS, ZMQ_SNDMORE);     // Alien data
        if (rc == -1){
            mvprintw(0,0,"--- ERROR ---\nFAILED TO PUBLISH MESSAGE 3");
            exit(0);
        }
        
        rc = zmq_send (socket, zaps, sizeof(pewpew_t)*2*16, ZMQ_SNDMORE);   //  Zaps iinformation
        if (rc == -1){
            mvprintw(0,0,"--- ERROR ---\nFAILED TO PUBLISH MESSAGE 4");
            exit(0);
        }
        
        rc = zmq_send (socket, &time, sizeof(time_t), ZMQ_SNDMORE);     // Time of the game
        if (rc == -1){
            mvprintw(0,0,"--- ERROR ---\nFAILED TO PUBLISH MESSAGE 5");
            exit(0);
        }

        rc = zmq_send (socket, &game, sizeof(int), 0);      // game status // if this int is 0 the game has ended
        if (rc == -1){
            mvprintw(0,0,"--- ERROR ---\nFAILED TO PUBLISH MESSAGE 6");
            exit(0);
        }
}

// Computes connection messages from the clients
int connect_msg (void* socket, int num_players, player_data_t players[8]){
    char resp[100];
    int rc, counter=0;
    /* If a new player can join, generate a new id and send his caracter and id*/
    if (num_players < 8){
        while (players[counter].id != -1)
            counter++;

        players[counter].id = random() % 1000;
        players[counter].score = 0;
        sprintf(resp, "%c, %d", players[counter].ch, players[counter].id);
        num_players++;
    }
    /* If can't join send -1*/
    else{
        strcpy(resp, "-1");
    }

    rc = zmq_send(socket, resp, sizeof(resp), 0);
    if (rc == -1){
        mvprintw(0,0,"--- ERROR ---\nFAILED TO SEND MESSAGE (connect_msg)");
        exit(0);
    }

    return num_players; // return new num_players
}

// Compute the new coordenates based on the direction received
void new_position(int x, int y, directions_ direction, player_data_t * player){
    switch (direction) // The following if clauses prevent the players to leave his allowed area
    {
    case UP:
        y --;
        if(y == 1)
            y = 2;
        break;
    case DOWN:
        y ++;
        if(y == WINDOW_SIZE-2)
            y = WINDOW_SIZE-3;
        break;
    case LEFT:
        x --;
        if(x ==1)
            x = 2;
        break;
    case RIGHT:
        x ++;
        if(x ==WINDOW_SIZE-2)
            x = WINDOW_SIZE-3;
        break;

    default:
        break;
    }

    player->x = x;
    player->y = y;

    return;

}

// Computes the players movement messages
void movement_msg(void *socket, player_data_t players[8], pewpew_t zaps[2][16], remote_char_t message, time_t msg_time){
    int idx = 0;
    int rc;

    // Finds the player that send the message
    while (message.ch != players[idx].ch && message.id != players[idx].id && idx < 8)
        idx++;
    if (idx == 8)
        return;

    // Sends the score back
    rc = zmq_send(socket,&players[idx].score,sizeof(int),0);
    if (rc == -1){
        mvprintw(0,0,"--- ERROR ---\nFAILED TO RECEIVE MESSAGE (movement_msg)");
        exit(0);
    }
    
    // Checks if the players is stuned
    if (difftime(msg_time, players[idx].stun) < 10)
        return;

    // Computes new position
    new_position(players[idx].x, players[idx].y,message.direction, &players[idx]);

    // Checks if player new place is in a zap
    if (players[idx].ch % 2 == 0) {
        //direction = 1 collumns
        if (zaps[1][players[idx].x - 2].player != -1 && difftime(msg_time, zaps[1][players[idx].x-2].time) < 0.5 && zaps[1][players[idx].x-2].player != idx){
            players[idx].stun = msg_time;
        }
    } else {
        //direction = 0 rows
        if (zaps[0][players[idx].y - 2].player != -1 && difftime(msg_time, zaps[0][players[idx].y-2].time) < 0.5 && zaps[0][players[idx].y - 2].player != idx){
            players[idx].stun = msg_time;
        }
    }

}

// Computes aliens moviment messages sent by the child process
void alien_message(void *socket, player_data_t players[8] , alien_data_t aliens[N_ALIENS], pewpew_t zaps[2][16], time_t msg_time, remote_char_t message){
    
    int rc;

    // Checks if the alien is still alive
    if (aliens[message.id].hp == 0){
        rc = zmq_send(socket, &aliens[message.id].hp, sizeof(int), 0);
        if (rc == -1){
        mvprintw(0,0,"--- ERROR ---\nFAILED TO SEND MESSAGE (alien_message)");
        exit(0);
    }
        return;
    }

    // Computes moviment
    switch (message.direction){
    case UP:
        if(aliens[message.id].y > 2){
           aliens[message.id].y--;
        } else
           aliens[message.id].y = 2; 
        break;
    case DOWN:
        if(aliens[message.id].y < WINDOW_SIZE-3){
            aliens[message.id].y++;
        } else
           aliens[message.id].y = WINDOW_SIZE-3; 
        break;
    case LEFT:
        if(aliens[message.id].x > 2)
            aliens[message.id].x --;
        break;
    case RIGHT:
        if(aliens[message.id].x < WINDOW_SIZE-3)
            aliens[message.id].x++;
        break;

    default:
        break;
    }

    // Checks if alien steps on a zap
    if (zaps[1][aliens[message.id].x - 2].player != -1 && difftime(msg_time, zaps[1][aliens[message.id].x-2].time) < 0.5){
        aliens[message.id].hp = 0;
        players[zaps[1][aliens[message.id].x - 2].player].score++;
    }

    if (zaps[0][aliens[message.id].y - 2].player != -1 && difftime(msg_time, zaps[0][aliens[message.id].y-2].time) < 0.5){
        aliens[message.id].hp = 0;
        players[zaps[0][aliens[message.id].y - 2].player].score++;
    }
    // Sends response
    rc = zmq_send(socket, &aliens[message.id].hp, sizeof(int), 0);
    if (rc == -1){
        mvprintw(0,0,"--- ERROR ---\nFAILED TO SEND MESSAGE (alien_message)");
        exit(0);
    }

}

// Computes zap messages
void zap_msg(void *socket, player_data_t players[8], remote_char_t message, time_t time, pewpew_t zaps[2][16], alien_data_t alien[N_ALIENS]){
    int idx = 0, direction, rc;

    // Finds the player that sent the message
    while (message.ch != players[idx].ch && message.id != players[idx].id && idx < 8)
        idx++;

    if (idx == 8)
        return;

    // checks is the zap coldown already pass
    if(difftime(time, players[idx].last_zap) < 3){
        rc = zmq_send(socket,&players[idx].score,sizeof(int),0);
        if (rc == -1){
            mvprintw(0,0,"--- ERROR ---\nFAILED TO SEND MESSAGE (zap_msg)");
            exit(0);
        }
        return;
    }
        
    // Cheks who was shot by the zap
    if (players[idx].ch % 2 == 0) {
        direction = 1;
        zaps[direction][players[idx].x-2].player = idx;
        zaps[direction][players[idx].x-2].time = time;
        // Players
        for (int i =0; i<8; i++){
            if(players[i].id != -1 && players[i].x == players[idx].x && i != idx){
                players[i].stun = time;
            }
        }
        // Aliens
        for (int i=0; i < N_ALIENS; i++) {   
            if(players[idx].x == alien[i].x && alien[i].hp != 0) {
                alien[i].hp = 0;
                players[idx].score++;
            } 
        }
    } else {
        direction = 0;
        zaps[direction][players[idx].y-2].player = idx;
        zaps[direction][players[idx].y-2].time = time;

        for (int i =0; i<8; i++){
            if(players[i].id != -1 && players[i].y == players[idx].y && i != idx){
                players[i].stun = time;
            }
        }

        for (int i=0; i < N_ALIENS; i++) {

            if(players[idx].y == alien[i].y  && alien[i].hp != 0) {
                alien[i].hp = 0;
                players[idx].score++;
            }
        }
    }

    players[idx].last_zap = time;
    // Sends the score of the player
    rc = zmq_send(socket,&players[idx].score,sizeof(int),0);
    if (rc == -1){
        mvprintw(0,0,"--- ERROR ---\nFAILED TO SEND MESSAGE (zap_msg)");
        exit(0);
    }

}

// Treats the disconnect message
int disconnect_msg(void *socket, int num_players, player_data_t players[8], remote_char_t message){
    int rc, i=0;
    
    // Finds the player that sent the message
    while (message.ch != players[i].ch && message.id != players[i].id && i < 8)
        i++;
    if (i == 8)
        return num_players;
    
    // Returns the final score of the player
    rc = zmq_send(socket,&players[i].score,sizeof(int),0);
    if (rc == -1){
        mvprintw(0,0,"--- ERROR ---\nFAILED TO SEND MESSAGE (disconnect_msg)");
        exit(0);
    }

    players[i].id = -1;
    players[i].score = 0;

    num_players--;


    return num_players;
}

// Manages the end of the game
int end_game(void *socket, player_data_t players[8], remote_char_t message, int num_players){

    int rc, i;
    int maxscore = 0;
    char end;
    // Clears the terminal
    for (int i = 0; i < 25; i++){
        mvprintw(i, 0, "                                                     ");
    }
    // Finds the player that won
    for(i = 0; i < 8; i++){

        if(players[i].score > players[maxscore].score)
            maxscore = i;
        }

    mvprintw(0,0,"Player %c won the game with score %d",players[maxscore].ch, players[maxscore].score);
    mvprintw(1,0,"Waiting for players to leave the game");

    refresh();
    // This while loop will return to all the players the end game event and if the player won
    while (num_players > 0){
        rc = zmq_recv (socket, &message, sizeof(remote_char_t), 0);
        if (rc == -1){
            mvprintw(0,0,"--- ERROR ---\nFAILED TO RECEIVE MESSAGE (end_game)");
            exit(0);
        }
        // messages from players
        if (message.msg_type != 4){
            // if the player won
            if(players[maxscore].ch == message.ch && players[maxscore].id == message.id){
                i = -1;
                rc = zmq_send (socket, &i, sizeof(int), 0);
                if (rc == -1){
                    mvprintw(0,0,"--- ERROR ---\nFAILED TO SEND MESSAGE (end_game)");
                    exit(0);
                }
            }
            // If the player lost
            else{
                i = -2;
                rc = zmq_send (socket, &i, sizeof(int), 0);
                if (rc == -1){
                    mvprintw(0,0,"--- ERROR ---\nFAILED TO SEND MESSAGE (end_game)");
                    exit(0);
                }
            }    
            num_players--;
            continue;
        }
        // If it's a message from the aliens (child)
        i=-1;
        rc = zmq_send (socket, &i, sizeof(int), 0);
        if (rc == -1){
            mvprintw(0,0,"--- ERROR ---\nFAILED TO SEND MESSAGE (end_game)");
            exit(0);
        }
    }

    return 0;
        
}







int main(){	
    int rc, num_players = 0, game = 1;
    char buffer[100];
    time_t msg_time;
    pewpew_t  zaps[2][16];
    remote_char_t message;
    player_data_t players[8];
    alien_data_t aliens [N_ALIENS];
    srandom(time(NULL));

    /* Inicialises the vector players with the carecters and inicial positions */
    for (int i = 0; i < 9; i++){
        players[i].ch = 'A' + i;
        players[i].id = -1;
        players[i].score = -1;
        players[i].stun = 0;
        players[i].last_zap = 0;
        switch (players[i].ch){
            case 'A':
                players[i].x = 0;
                players[i].y = 9;
                break;
            case 'B':
                players[i].x = 9;
                players[i].y = 19;
                break;
            case 'C':
                players[i].x = 19;
                players[i].y = 10;
                break;
            case 'D':
                players[i].x = 10;
                players[i].y = 0;
                break;
            case 'E':
                players[i].x = 1;
                players[i].y = 10;
                break;
            case 'F':
                players[i].x = 10;
                players[i].y = 18;
                break;
            case 'G':
                players[i].x = 18;
                players[i].y = 9;
                break;
            case 'H':
                players[i].x = 9;
                players[i].y = 1;
                break;
            
            default:
                break;
        }
        
    }

    /* Inicialises the vector aliens with hp=1 and random inicial positions */
    for (int i = 0; i < N_ALIENS; i++){
        aliens[i].hp = 1;
        aliens[i].x = random()%16 + 2;
        aliens[i].y = random()%16 + 2;
    }

    /* Inicialises the vector zaps with player = -1 and time = 0 */
    for(int i=0; i<2; i++){
        for (int j=0; j<16; j++){
            zaps[i][j].player = -1;
            zaps[i][j].time = 0;
        }
    }

    /* Declare and bind socket to comunicate with the display using the SUB/PUB patern */
    sprintf(buffer,"tcp://*:%d",PORT_SP);
    void *context_SP = zmq_ctx_new ();
    void *responder_SP = zmq_socket (context_SP, ZMQ_PUB);
    rc = zmq_bind (responder_SP, buffer);

    if (rc == -1){
        printf("--- ERROR ---\nBINDING TO PORT %d FAILED\n", PORT_SP);
        exit(0);
    }

    /* Declare and bind socket to comunicate with astronauts using the REP/REQ patern */
    sprintf(buffer,"tcp://*:%d",PORT_RR);
    void *context_RR = zmq_ctx_new ();
    void *responder_RR = zmq_socket (context_RR, ZMQ_REP);
    rc = zmq_bind (responder_RR, buffer);

    if (rc == -1){
        printf("--- ERROR ---\nBINDING TO PORT %d FAILED\n", PORT_RR);
        exit(0);
    }

    pid_t pid = fork();

    if (pid == -1){
        printf("--- ERROR ---\nFork unsucessful\n");
        exit (0);
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    else if (pid == 0){     // Child code:
        // Connects to the parent
        sprintf(buffer,"tcp://%s:%d",IP_ADRESS,PORT_RR);
        void *context_child = zmq_ctx_new ();
        void *requester_child = zmq_socket (context_child, ZMQ_REQ);
        rc = zmq_connect (requester_child,buffer);
        if (rc == -1){
            printf("--- ERROR ---\nCHILD FAILED TO BIND TO PORT %d\n",PORT_RR);
        }
        // alien movement messages
        message.msg_type = 4;
        int resp;

        while (1){
            // 1s dellay
            sleep (1);
            // sends one message with a random movement of a alien
            for (int i=0; i<N_ALIENS; i++){
                if (aliens[i].hp == 1){
                    message.id = i;
                    message.direction = random() % 4;
                    rc = zmq_send (requester_child, &message, sizeof(message), 0);
                    if (rc == -1){
                        mvprintw(0,0,"--- ERROR ---\nFAILED TO SEND MESSAGE");
                        exit(0);
                    }
                    rc = zmq_recv (requester_child, &resp, sizeof(int), 0);
                    if (rc == -1){
                        mvprintw(0,0,"--- ERROR ---\nFAILED TO RECEIVE MESSAGE");
                        exit(0);
                    }
                    if (resp != -1)
                        aliens[i].hp = resp;
                    else// end game situation
                        break;
                }
            }
            if (resp == -1)
                break;
        }
        zmq_close(requester_child);
        zmq_ctx_destroy(context_child);
     }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    else{ // Parent code

    // ncurses initialization
	initscr();		    	
	cbreak();				
    keypad(stdscr, TRUE);   
	noecho();		


    /* creates the windows and draws the borders of the outer-space and the score board */
    WINDOW * space = newwin(22, 22, 1, 1);
    WINDOW * score_board = newwin(22, 22, 1, 24);
    box(space, 0, 0);
    box(score_board, 0, 0);
    
    mvprintw(0, 2, "12345678901234567890");
    for (int i = 1; i < 10; i++){
        mvaddch(i+1, 0, i+48);
        mvaddch(i+11, 0, i+48);
    }
    mvaddch(11, 0, '0');
    mvaddch(21, 0, '0');

    mvwprintw(score_board, 2, 4, "SCORE:");

    refresh();
    wrefresh(space);
    wrefresh(score_board);
    // Game Loop
    while (game){
        
        rc = zmq_recv(responder_RR, &message, sizeof(remote_char_t), 0);

        msg_time = time(NULL);

        if (rc == -1){
            mvprintw(0,0,"--- ERROR ---\nFAILED TO RECEIVE MESSAGE");
            exit(0);
        }
        
        if (message.msg_type == 0){
            num_players = connect_msg(responder_RR, num_players, players); 
            
        }
        else if (message.msg_type == 1){
            movement_msg(responder_RR, players, zaps, message, msg_time); 

        }
        else if (message.msg_type == 2){
            zap_msg(responder_RR, players, message, msg_time, zaps ,aliens); 
        }
        else if (message.msg_type == 3){
            num_players = disconnect_msg(responder_RR, num_players, players, message);
        }
        else if (message.msg_type == 4){
            alien_message(responder_RR, players, aliens, zaps, msg_time, message);
        }
        else {
            mvprintw(0,0,"--- ERROR ...\nINVALID MESSAGE TYPE");
        }
        // Updates the displays from the server and outer-space-display
        outer_space_update(responder_SP, players, aliens, zaps, msg_time, 1);
        display(players, aliens, zaps, msg_time, space, score_board);
        int i;
        // Checks if the game ended
        for(i=0; i<N_ALIENS; i++){
            if (aliens[i].hp == 1)
                break;
        }
        if(i==N_ALIENS){
            outer_space_update(responder_SP, players, aliens, zaps, msg_time, 0);
            game = end_game(responder_RR, players,message, num_players);   
        }    

    }

    endwin(); // End curses mode
    zmq_close (responder_RR);
    zmq_close (responder_SP);
    zmq_ctx_destroy (context_RR);
    zmq_ctx_destroy (context_SP);
    return 0;
    }
}