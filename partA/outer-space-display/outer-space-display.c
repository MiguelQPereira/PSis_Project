#include "structs.h"

int main (){

    char buffer[100];
    char type[100];
    int xy[2];
    int rc;

    /* Declare and bind socket to comunicate with astronauts using the REP/REQ patern */
    sprintf(buffer,"tcp://%s:%d",IP_ADRESS,PORT_SP);
    void *context = zmq_ctx_new ();
    void *subscriber = zmq_socket (context, ZMQ_REQ);
    rc = zmq_connect (subscriber,buffer);
    if (rc == -1){
        printf("--- ERROR ---\nBINDING TO PORT %d FAILED\n",PORT_SP);
    }
    
    zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE,"ALIEN", strlen("ALIEN"));
    zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE,"PLAYER", strlen("PLAYER"));
    zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE,"ZAP", strlen("ZAP"));
    zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE,"DISCONNECT", strlen("DISCONNECT"));
    
    

    while(1) {
        
        rc = zmq_recv(subscriber, type, 100, 0);
        if (rc == -1){
            printf("--- ERROR ---\nFAILED TO RECEIVE MESSAGE\n");
            exit(0);
        }
        if(strcmp(type,"ALIEN")) {
            alien_data_t alien;
            rc = zmq_recv(subscriber, &alien, sizeof(alien_data_t), 0);
            if (rc == -1){
            printf("--- ERROR ---\nFAILED TO RECEIVE MESSAGE\n");
            exit(0);
            }
            rc = zmq_recv(subscriber, xy, sizeof(xy), 0);
            if (rc == -1){
            printf("--- ERROR ---\nFAILED TO RECEIVE MESSAGE\n");
            exit(0);
            }
        }
            
        else if(strcmp(type,"PLAYER")) {

            player_data_t player;
            rc = zmq_recv(subscriber, &player, sizeof(player_data_t), 0);
            if (rc == -1){
            printf("--- ERROR ---\nFAILED TO RECEIVE MESSAGE\n");
            exit(0);
            }
            rc = zmq_recv(subscriber, xy, sizeof(xy), 0);
            if (rc == -1){
            printf("--- ERROR ---\nFAILED TO RECEIVE MESSAGE\n");
            exit(0);
            }

        }
        else if(strcmp(type,"ZAP")) {
            return 0;
        }
        else if(strcmp(type,"DISCONNECT")) {

            rc = zmq_recv(subscriber, xy, sizeof(xy), 0);
            if (rc == -1){
            printf("--- ERROR ---\nFAILED TO RECEIVE MESSAGE\n");
            exit(0);
            }

        }
       
        free(type);
    }
    
    zmq_close (subscriber);
    zmq_ctx_destroy (context);
    return 0;
}