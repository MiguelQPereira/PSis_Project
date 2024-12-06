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

int connect_msg (void* socket, int num_players, player_data_t players[8], WINDOW * space, WINDOW * score_board){
    char resp[100];
    int rc, counter=0;
    /* If a new player can join, generate a new id and send his caracter and id*/
    if (num_players < 8){
        while (players[counter].id != -1)
            counter++;

        players[counter].id = random() % 1000;
        sprintf(resp, "%c, %d", players[counter].ch, players[counter].id);
        //outer_space_update(1,socket,(void*)&player,player.x,player.y,0);
        num_players++;
    }
    /* If can't join send -1*/
    else{
        strcpy(resp, "-1");
    }

    zmq_send(socket, resp, sizeof(resp), 0);
    if (rc == -1){
        mvprintw(0,0,"--- ERROR ---\nFAILED TO SEND MESSAGE (connect_msg)");
        exit(0);
    }

    display(1, (void*) &players[counter], players[counter].x, players[counter].y, 0, space, score_board);

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

void movement_msg(void *socket, player_data_t players[8], remote_char_t message, WINDOW * space, WINDOW * score_board){
    //Needs entity of player, x_old, y_old, flag for zap and two pointers  
    int xy[2];
    int i = 0;
    int rc;

    while (message.ch != players[i].ch && message.id != players[i].id && i < 8)
        i++;
    if (i == 8)
        return;

    rc = zmq_send(socket,&players[i].score,sizeof(int),0);

    xy[0] = players[i].x;
    xy[1] = players[i].y;

    new_position(xy[0], xy[1],message.direction, &players[i]);
    
    display(1, (void*) &players[i], xy[0], xy[1], 0, space, score_board);

}

void zap_msg(void *socket, player_data_t players[8], remote_char_t message, WINDOW * space, WINDOW * score_board, time_t time){
    int i = 0;
    int rc;

    while (message.ch != players[i].ch && message.id != players[i].id && i < 8)
        i++;
    if (i == 8)
        return;




    rc = zmq_send(socket,&players[i].score,sizeof(int),0);
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
        return;
    
    rc = zmq_send(socket,&players[i].score,sizeof(int),0);
    if (rc == -1){
        mvprintw(0,0,"--- ERROR ---\nFAILED TO SEND MESSAGE (disconnect_msg)");
        exit(0);
    }

    players[i].id = -1;
    players[i].score = 0;

    num_players--;
    
    display(3, (void*) &players[i], players[i].x, players[i].y, 0, space, score_board);


    return num_players;
}


int main(){	
    int rc, num_players = 0;
    char buffer[100];
    time_t row_zap[16], col_zap[16], msg_time;
    remote_char_t message;
    player_data_t players[8];

    /* Inicialises the vector player with the carecters and inicial positions */
    for (int i = 0; i < 9; i++){
        players[i].ch = 'A' + i;
        players[i].id = -1;
        players[i].score = 0;
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

        if (rc == -1){
            mvprintw(0,0,"--- ERROR ---\nFAILED TO RECEIVE MESSAGE");
            exit(0);
        }
        
        if (message.msg_type == 0){
            num_players = connect_msg(responder_RR, num_players, players, space, score_board); // Send connect message to astronaut client
            
        }
        else if (message.msg_type == 1){
            movement_msg(responder_RR, players, message,space, score_board); //Send movement message to astronaut client

        }
        else if (message.msg_type == 2){
            zap_msg(responder_RR, players, message, space, score_board, msg_time); //Send zap message to astronaut client
        }
        else if (message.msg_type == 3){
            num_players = disconnect_msg(responder_RR, num_players, players, message, space, score_board); //Send disconnect message to astronaut client
        }
        else {
            mvprintw(0,0,"--- ERROR ...\nINVALID MESSAGE TYPE");
        }		 
    }

    endwin(); // End curses mode
    zmq_close (responder_RR);
    zmq_ctx_destroy (context_RR);
    return 0;
}