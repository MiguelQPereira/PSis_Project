#include "../others/display.h"
#include "high_score.pb-c.h"


int game = 1; // Variable to control the game status

time_t last_kill = 0; // Variable to control the last kill of an alien

pthread_mutex_t lock_alien = PTHREAD_MUTEX_INITIALIZER; // Mutex to control the access to the last kill variable

// Sends the messages to the outer-space display with the information to print
void outer_space_update(void *socket, player_data_t players[8], alien_data_t aliens[N_ALIENS], pewpew_t zaps[2][16], time_t time , int play) {
    
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

        rc = zmq_send (socket, &play, sizeof(int), 0);      // game status // if this int is 0 the game has ended
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
    if (aliens[message.id].hp == -1){
        aliens[message.id].hp = 0;
        rc = zmq_send(socket, &aliens[message.id].hp, sizeof(int), 0);
        if (rc == -1){
        mvprintw(0,0,"--- ERROR ---\nFAILED TO SEND MESSAGE (alien_message)");
        exit(0);
    }
        return;
    }
    if (aliens[message.id].hp == 0){
        aliens[message.id].hp =1;
        aliens[message.id].x = random()%16 + 2;
        aliens[message.id].y = random()%16 + 2;
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
        pthread_mutex_lock(&lock_alien);
            last_kill = msg_time;
        pthread_mutex_unlock(&lock_alien);
    }

    if (zaps[0][aliens[message.id].y - 2].player != -1 && difftime(msg_time, zaps[0][aliens[message.id].y-2].time) < 0.5){
        aliens[message.id].hp = 0;
        players[zaps[0][aliens[message.id].y - 2].player].score++;
        pthread_mutex_lock(&lock_alien);
            last_kill = msg_time;
        pthread_mutex_unlock(&lock_alien);
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
                alien[i].hp = -1;
                players[idx].score++;
                pthread_mutex_lock(&lock_alien);
                    last_kill = time;
                pthread_mutex_unlock(&lock_alien);
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
                alien[i].hp = -1;
                players[idx].score++;
                pthread_mutex_lock(&lock_alien);
                    last_kill = time;
                pthread_mutex_unlock(&lock_alien);
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
    int alien = 1;
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
    while (num_players > 0 || alien){
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
        }else {
            alien = 0;
            // If it's a message from the aliens
            i=-1;
            rc = zmq_send (socket, &i, sizeof(int), 0);
            if (rc == -1){
                mvprintw(0,0,"--- ERROR ---\nFAILED TO SEND MESSAGE (end_game)");
                exit(0);
            }
        }
        
    }
    mvprintw(1,0,"Press q/Q to quit                    ");
    refresh();

    return 0;
        
}

void * aliens_movement(void *arg){

    char buffer[100];
    int rc, alive = N_ALIENS;
    remote_char_t message;
    alien_data_t aliens[N_ALIENS];

    alien_data_t * alien_arg = (alien_data_t*) arg;
    for (int i=0; i<N_ALIENS; i++){
        aliens[i].hp = alien_arg[i].hp;  
        aliens[i].x = alien_arg[i].x;
        aliens[i].y = alien_arg[i].y;
    }

    free(alien_arg);

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
        alive = 0;
        // 1s delay
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
                if (resp != -1){
                    alive += resp;
                    aliens[i].hp = resp;
                } 
                else// end game situation
                    break;
            }
        }
        if (resp == -1)
            break;
        
        if(difftime(time(NULL), last_kill) > 10 && alive < N_ALIENS){
            int childs = alive * 0.1;
            for (int i=0; i<N_ALIENS; i++){
                while (aliens[i].hp!=0){
                    i++;
                }
                aliens[i].hp = 1;
                childs--;
                if(childs == 0)
                    break;
                
            }
        }
    }
    zmq_close(requester_child);
    zmq_ctx_destroy(context_child);


}

void * quit(){

    char c;
    while(game){
        c = getch();
        if (c == 'q' || c == 'Q'){
            game = 0;
        }
    }
}

int main(){
    	
    int rc, num_players = 0;
    char buffer[100];
    time_t msg_time;
    pewpew_t  zaps[2][16];
    remote_char_t message;
    player_data_t players[8];
    alien_data_t aliens [N_ALIENS], *alien_arg;
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

    /* Declare and bind socket to comunicate with the high-score using the SUB/PUB patern */
    sprintf(buffer,"tcp://*:%d",PORT_HS);
    void *context_HS = zmq_ctx_new ();
    void *publisher_HS = zmq_socket (context_HS, ZMQ_PUB);
    rc = zmq_bind (publisher_HS, buffer);

    if (rc == -1){
        printf("--- ERROR ---\nBINDING TO PORT %d FAILED\n", PORT_HS);
        exit(0);
    }



    alien_arg = malloc (N_ALIENS * sizeof(alien_data_t));

    for (int i=0; i<N_ALIENS; i++){
        alien_arg[i].hp = aliens[i].hp;
        alien_arg[i].x = aliens[i].x;
        alien_arg[i].y = aliens[i].y;
    }

    long int thread_aliens_movement_id;
    int check;
    thread_aliens_movement_id = 1;

    check = pthread_create(&thread_aliens_movement_id, NULL, aliens_movement, alien_arg);
    if (check != 0) {
        printf("--- ERROR ---\nCOULDN'T CREATE ALIEN MOVEMENT THREAD THREAD");
        exit(1);
    }

    // ncurses initialization
    initscr();		    	
    cbreak();				
    keypad(stdscr, TRUE);   
    noecho();
    refresh();	

    long int thread_quit_id;
    thread_quit_id = 2;

    check = pthread_create(&thread_quit_id, NULL, quit, NULL);
    if (check != 0) {
        printf("--- ERROR ---\nCOULDN'T CREATE QUIT THREAD");
        exit(1);
    }

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

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Proto Buffers Zone //

        HighScore msgHS = HIGH_SCORE__INIT;

        msgHS.has_game = 0;

        if (players[0].id != -1){
            msgHS.has_pa = 1;
            msgHS.pa = players[0].score;
        }
        else{
            msgHS.has_pa = 0;
        }

        if (players[1].id != -1){
            msgHS.has_pb = 1;
            msgHS.pb = players[1].score;
        }
        else{
            msgHS.has_pb = 0;
        }
        
        if (players[2].id != -1){
            msgHS.has_pc = 1;
            msgHS.pc = players[2].score;
        }
        else{
            msgHS.has_pc = 0;
        }
        
        if (players[3].id != -1){
            msgHS.has_pd = 1;
            msgHS.pd = players[3].score;
        }
        else{
            msgHS.has_pd = 0;
        }
        
        if (players[4].id != -1){
            msgHS.has_pe = 1;
            msgHS.pe = players[4].score;
        }
        else{
            msgHS.has_pe = 0;
        }
        
        if (players[5].id != -1){
            msgHS.has_pf = 1;
            msgHS.pf = players[5].score;
        }
        else{
            msgHS.has_pf = 0;
        }
        
        if (players[6].id != -1){
            msgHS.has_pg = 1;
            msgHS.pg = players[2].score;
        }
        else{
            msgHS.has_pg = 0;
        }
        
        if (players[7].id != -1){
            msgHS.has_ph = 1;
            msgHS.ph = players[7].score;
        }
        else{
            msgHS.has_ph = 0;
        }

        size_t msgHS_size = high_score__get_packed_size(&msgHS);
        char *msgHS_packed = malloc(msgHS_size);

        high_score__pack(&msgHS, msgHS_packed);


        zmq_msg_t zmq_message;
        zmq_msg_init_size(&zmq_message, msgHS_size);
        memcpy(zmq_msg_data(&zmq_message), msgHS_packed, msgHS_size);
        zmq_msg_send(&zmq_message, publisher_HS, 0);
        zmq_msg_close(&zmq_message);

        free(msgHS_packed);
        
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        int i;
        // Checks if the game ended
        for(i=0; i<N_ALIENS; i++){
            if (aliens[i].hp == 1)
                break;
        }
        if(i==N_ALIENS){
            game = 0; 
        }    

    }
    outer_space_update(responder_SP, players, aliens, zaps, msg_time, 0);
    end_game(responder_RR, players,message, num_players);

    // Wait for threads to finish
    pthread_join(thread_aliens_movement_id, NULL);
    pthread_join(thread_quit_id, NULL);

    HighScore msgHS = HIGH_SCORE__INIT;
    msgHS.has_game = 1;
    msgHS.game = 1;
    size_t msgHS_size = high_score__get_packed_size(&msgHS);
    char *msgHS_packed = malloc(msgHS_size);

    high_score__pack(&msgHS, msgHS_packed);


    zmq_msg_t zmq_message;
    zmq_msg_init_size(&zmq_message, msgHS_size);
    memcpy(zmq_msg_data(&zmq_message), msgHS_packed, msgHS_size);
    zmq_msg_send(&zmq_message, publisher_HS, 0);
    zmq_msg_close(&zmq_message);

    free(msgHS_packed);

    endwin(); // End curses mode
    zmq_close (responder_RR);
    zmq_close (responder_SP);
    zmq_ctx_destroy (context_RR);
    zmq_ctx_destroy (context_SP);
    return 0;
}