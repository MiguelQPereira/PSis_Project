#include "display.h"

void outer_space_update( int type, void *socket, void* entity, int x_old, int y_old, int zap) {
    
    int rc, xy[2];
    xy[0] = x_old;
    xy[1] = y_old;
    
    // alien movement
    if (type == 0){
        rc = zmq_send (socket, "ALIEN", strlen ("ALIEN"), ZMQ_SNDMORE);
        if (rc == -1){
            mvprintw(0,0,"--- ERROR ---\nFAILED TO PUBLISH MESSAGE");
            exit(0);
        }

        rc = zmq_send(socket, entity, sizeof(entity), ZMQ_SNDMORE);
        if (rc == -1){
            mvprintw(0,0,"--- ERROR ---\nFAILED TO PUBLISH MESSAGE");
            exit(0);
        }

        rc = zmq_send(socket, xy, sizeof(xy), 0);
        if (rc == -1){
            mvprintw(0,0,"--- ERROR ---\nFAILED TO PUBLISH MESSAGE");
            exit(0);
        }
    }
    // player movement
    else if(type == 1){
        rc = zmq_send (socket, "PLAYER", strlen ("PLAYER"), ZMQ_SNDMORE);
        if (rc == -1){
            mvprintw(0,0,"--- ERROR ---\nFAILED TO PUBLISH MESSAGE");
            exit(0);
        }

        rc = zmq_send(socket, entity, sizeof(player_data_t), ZMQ_SNDMORE);
        if (rc == -1){
            mvprintw(0,0,"--- ERROR ---\nFAILED TO PUBLISH MESSAGE");
            exit(0);
        }
        rc = zmq_send(socket, xy, sizeof(xy), 0);
        if (rc == -1){
            mvprintw(0,0,"--- ERROR ---\nFAILED TO PUBLISH MESSAGE");
            exit(0);
        }
    }
    // zap
    else if(type == 2){

    }
    // delete entity
    else if(type == 3) {

        rc = zmq_send (socket, "DISCONNECT", strlen ("DISCONNECT"), ZMQ_SNDMORE);
        if (rc == -1){
            mvprintw(0,0,"--- ERROR ---\nFAILED TO PUBLISH MESSAGE");
            exit(0);
        }

        rc = zmq_send(socket, xy, sizeof(xy), 0);
        if (rc == -1){
            mvprintw(0,0,"--- ERROR ---\nFAILED TO PUBLISH MESSAGE");
            exit(0);
       }        
        
    }
}

int connect_msg (void* socket, int num_players, player_data_t players[8]){
    char resp[100];
    int rc, counter=0;
    /* If a new player can join, generate a new id and send his caracter and id*/
    if (num_players < 8){
        while (players[counter].id != -1)
            counter++;

        players[counter].id = random() % 1000;
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

void new_position(int x, int y, directions_ direction, player_data_t * player){
    switch (direction)
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
    case ZAP:
        //Para Miguel elaborar
    case QUIT:

    default:
        break;
    }

    player->x = x;
    player->y = y;

    return;

}

void movement_msg(void *socket, player_data_t players[8], pewpew_t zaps[2][16], remote_char_t message, WINDOW * space, WINDOW * score_board, time_t msg_time){
    int idx = 0;
    int rc;

    while (message.ch != players[idx].ch && message.id != players[idx].id && idx < 8)
        idx++;
    if (idx == 8)
        return;

    rc = zmq_send(socket,&players[idx].score,sizeof(int),0);

    if (difftime(msg_time, players[idx].stun) < 10)
        return;

    new_position(players[idx].x, players[idx].y,message.direction, &players[idx]);

    if (players[idx].ch % 2 == 0) {
        //direction = 1;
        if (zaps[1][players[idx].x - 2].player != -1 && difftime(msg_time, zaps[1][players[idx].x-2].time) < 0.5){
            players[idx].stun = msg_time;
        }
    } else {
        //direction = 0;
        if (zaps[0][players[idx].y - 2].player != -1 && difftime(msg_time, zaps[1][players[idx].y-2].time) < 0.5){
            players[idx].stun = msg_time;
        }
    }

}

void zap_msg(void *socket, player_data_t players[8], remote_char_t message, WINDOW * space, WINDOW * score_board, time_t time, pewpew_t zaps[2][16], time_t msg_time){
    int idx = 0, direction, rc;

    while (message.ch != players[idx].ch && message.id != players[idx].id && idx < 8)
        idx++;
    if (idx == 8)
        return;

    if (players[idx].ch % 2 == 0) {
        direction = 1;
        zaps[direction][players[idx].x-2].player = idx;
        zaps[direction][players[idx].x-2].time = time;

        for (int i =0; i<8; i++){
            if(players[i].id != -1 && players[i].x == players[idx].x && i != idx){
                players[i].stun = time;
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
    }

    players[idx].last_zap = time;

    rc = zmq_send(socket,&players[idx].score,sizeof(int),0);
    if (rc == -1){
        mvprintw(0,0,"--- ERROR ---\nFAILED TO SEND MESSAGE (zap_msg)");
        exit(0);
    }

}

int disconnect_msg(void *socket,int num_players, player_data_t players[8], remote_char_t message, WINDOW * space, WINDOW * score_board){
    int rc, i=0;
    
    while (message.ch != players[i].ch && message.id != players[i].id && i < 8)
        i++;
    if (i == 8)
        return num_players;
    
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


int main(){	
    int rc, num_players = 0;
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
        players[i].score = 0;
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

    /* Declare and bind socket to comunicate with astronauts using the REP/REQ patern */
    sprintf(buffer,"tcp://*:%d",PORT_RR);
    void *context_RR = zmq_ctx_new ();
    void *responder_RR = zmq_socket (context_RR, ZMQ_REP);
    rc = zmq_bind (responder_RR, buffer);

    if (rc == -1){
        printf("--- ERROR ---\nBINDING TO PORT %d FAILED\n", PORT_RR);
        exit(0);
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

    mvwprintw(score_board, 2, 4, "SCORE");

    refresh();
    wrefresh(space);
    wrefresh(score_board);

    while (1){
        
        rc = zmq_recv(responder_RR, &message, sizeof(remote_char_t), 0);

        msg_time = time(NULL);

        /*for (int i=0; i<2; i++){
            for (int j=0; j<16; j++){
                if (difftime(msg_time, zaps[i][j].time) > 0.5 && zaps[i][j].time != 0.0){
                    zaps[i][j].time = 0.0;
                }    
            }
        }*/

        if (rc == -1){
            mvprintw(0,0,"--- ERROR ---\nFAILED TO RECEIVE MESSAGE");
            exit(0);
        }
        
        if (message.msg_type == 0){
            num_players = connect_msg(responder_RR, num_players, players); // Send connect message to astronaut client
            
        }
        else if (message.msg_type == 1){
            movement_msg(responder_RR, players, zaps, message,space, score_board, msg_time); //Send movement message to astronaut client

        }
        else if (message.msg_type == 2){
            zap_msg(responder_RR, players, message, space, score_board, msg_time, zaps, msg_time); //Send zap message to astronaut client
        }
        else if (message.msg_type == 3){
            num_players = disconnect_msg(responder_RR, num_players, players, message, space, score_board); //Send disconnect message to astronaut client
        }
        else {
            mvprintw(0,0,"--- ERROR ...\nINVALID MESSAGE TYPE");
        }	

        /* TO DO : timer of lazers */

        display(players, aliens, zaps, msg_time, space, score_board);	 
    }

    endwin(); // End curses mode
    zmq_close (responder_RR);
    zmq_ctx_destroy (context_RR);
    return 0;
}