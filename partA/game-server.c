#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <zmq.h>

#include "structs.h"

int connect_msg (void* socket, int num_players, server_data_t player){
    char resp[100];
    int rc;
    /* If a new player can join, generate a new id and send his caracter and id*/
    if (num_players < 9){
        player.id = random() % 1000;
        sprintf(resp, "%c, %d", player.ch, player.id);
        num_players++;
    }
    /* If can't join send -1*/
    else{
        strcpy(resp, "-1");
    }

    zmq_send(socket, resp, sizeof(resp), 0);
    if (rc == -1){
        printf("--- ERROR ---\nFAILED TO SEND MESSAGE (connect_msg)\n");
        exit(0);
    }

    return num_players; // return new num_players or -1 if can't join
}

void movement_msg(){
    printf("--- ERROR ---\nFUNCTION NOT IMPLEMENTED (connect_msg)\n");
    exit(0);
}

void zap_msg(){
    printf("--- ERROR ---\nFUNCTION NOT IMPLEMENTED (connect_msg)\n");
    exit(0);
}

void disconnect_msg(){
    printf("--- ERROR ---\nFUNCTION NOT IMPLEMENTED (connect_msg)\n");
    exit(0);
}


int main(){	
    int rc, num_players = 0;
    char buffer[100];
    remote_char_t message;
    server_data_t players[8];

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
    while (1){
        rc = zmq_recv(responder_RR, &message, sizeof(remote_char_t), 0);
        if (rc == -1){
            printf("--- ERROR ---\nFAILED TO RECEIVE MESSAGE\n");
            exit(0);
        }
        
        if (message.msg_type == 0){
            num_players = connect_msg(responder_RR, num_players, players[num_players]);
        }
        else if (message.msg_type == 1){
            movement_msg();
        }
        else if (message.msg_type == 2){
            zap_msg();
        }
        else if (message.msg_type == 3){
            disconnect_msg();
        }
        else {
            printf("--- ERROR ...\nINVALID MESSAGE TYPE\n");
            exit(0);
        }
        
    }
}