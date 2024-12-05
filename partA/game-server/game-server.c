#include "structs.h"

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

int connect_msg (void* socket, int num_players, player_data_t player){
    char resp[100];
    int rc;
    /* If a new player can join, generate a new id and send his caracter and id*/
    if (num_players < 9){
        player.id = random() % 1000;
        sprintf(resp, "%c, %d", player.ch, player.id);
        outer_space_update(1,socket,(void*)&player,player.x,player.y,0);
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

    return num_players; // return new num_players or -1 if can't join
}

void movement_msg(void *socket,int num_players, player_data_t player){
    int rc;
    rc = zmq_send(socket,&player,sizeof(player),0);
    if (rc == -1){
        mvprintw(0,0,"--- ERROR ---\nFAILED TO SEND MESSAGE (movement_msg)");
        exit(0);
    }

}

void zap_msg(void *socket,int num_players, player_data_t player){
    int rc;
    rc = zmq_send(socket,&player,sizeof(player),0);
    if (rc == -1){
        mvprintw(0,0,"--- ERROR ---\nFAILED TO SEND MESSAGE (zap_msg)");
        exit(0);
    }

}

void disconnect_msg(void *socket,int num_players, player_data_t player){
    int rc;
    rc = zmq_send(socket,&player,sizeof(player),0);
    if (rc == -1){
        mvprintw(0,0,"--- ERROR ---\nFAILED TO SEND MESSAGE (disconnect_msg)");
        exit(0);
    }

}

void new_position(int* x, int *y, directions_ direction){
    switch (direction)
    {
    case UP:
        (*x) --;
        if(*x ==0)
            *x = 2;
        break;
    case DOWN:
        (*x) ++;
        if(*x ==WINDOW_SIZE-1)
            *x = WINDOW_SIZE-3;
        break;
    case LEFT:
        (*y) --;
        if(*y ==0)
            *y = 2;
        break;
    case RIGHT:
        (*y) ++;
        if(*y ==WINDOW_SIZE-1)
            *y = WINDOW_SIZE-3;
        break;
    case ZAP:
        //Para Miguel elaborar
    case QUIT:

    default:
        break;
    }

}

int main(){	
    int rc, num_players = 0;
    char buffer[100];
    remote_char_t message;
    player_data_t players[8];

    /* Inicialises the vector player with the carecters and inicial positions */
    for (int i = 0; i < 9; i++){
        players[i].ch = 'A' + i;
        players[i].id = -1;
        switch (players[i].ch){
            case 'A':
                players[i].x = 9;
                players[i].y = 1;
                break;
            case 'B':
                players[i].x = 18;
                players[i].y = 9;
                break;
            case 'C':
                players[i].x = 9;
                players[i].y = 18;
                break;
            case 'D':
                players[i].x = 1;
                players[i].y = 9;
                break;
            case 'E':
                players[i].x = 9;
                players[i].y = 0;
                break;
            case 'F':
                players[i].x = 19;
                players[i].y = 18;
                break;
            case 'G':
                players[i].x = 9;
                players[i].y = 19;
                break;
            case 'H':
                players[i].x = 0;
                players[i].y = 9;
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


    /* creates a window and draws a border */
    WINDOW * my_win = newwin(WINDOW_SIZE, WINDOW_SIZE, 0, 0);
    box(my_win, 0 , 0);	
	wrefresh(my_win);



    while (1){
        rc = zmq_recv(responder_RR, &message, sizeof(remote_char_t), 0);
        if (rc == -1){
            mvprintw(0,0,"--- ERROR ---\nFAILED TO RECEIVE MESSAGE");
            exit(0);
        }
        
        if (message.msg_type == 0){
            num_players = connect_msg(responder_RR, num_players, players[num_players]); // Send connect message to astronaut client
            
        }
        else if (message.msg_type == 1){
            movement_msg(responder_RR, num_players, players[num_players]); //Send movement message to astronaut client

        }
        else if (message.msg_type == 2){
            zap_msg(responder_RR, num_players, players[num_players]); //Send zap message to astronaut client
        }
        else if (message.msg_type == 3){
            disconnect_msg(responder_RR, num_players, players[num_players]); //Send disconnect message to astronaut client
        }
        else {
            mvprintw(0,0,"--- ERROR ...\nINVALID MESSAGE TYPE");
            exit(0);
        }
        wrefresh(my_win);		

        
    }

    endwin(); // End curses mode
    zmq_close (responder_RR);
    zmq_ctx_destroy (context_RR);
    return 0;
}