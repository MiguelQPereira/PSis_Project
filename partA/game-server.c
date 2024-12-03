#include <sdtio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <zmq.h>

#include "structs.h"

int main()
{	
    int rc, num_players = 0;
    char buffer[100], resp;
    remote_char_t message;
    server_data_t player[8];

    /* Declare and bind socket to comunicate with astronauts using the REP/REQ patern */
    sprintf(buffer,"tcp://*:%d\0",PORT_RR);
    void *context_RR = zmq_ctx_new ();
    void *responder_RR = zmq_socket (context_RR, ZMQ_REP);
    rc = zmq_bind (responder_RR, buffer);

    if (rc == -1){
        printf("--- ERROR ---\nBinding to port %d failed\n", PORT_RR);
    }


    /* Declare and bind socket to comunicate with the display using the SUB/PUB patern */
    sprintf(buffer,"tcp://*:%d\0",PORT_SP);
    void *context_SP = zmq_ctx_new ();
    void *responder_SP = zmq_socket (context_SP, ZMQ_PUB);
    rc = zmq_bind (responder_SP, buffer);

    if (rc == -1){
        printf("--- ERROR ---\nBinding to port %d failed\n", PORT_SP);
    }
    while (1){
        zmq_recv(responder_RR, &message, sizeof(remote_char_t), 0);

        if (num_players < 9){
            
        }

        zmq_send(responder_RR, resp, sizeof(resp), 0);
    }
}