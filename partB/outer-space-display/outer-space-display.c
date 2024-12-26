#include "../others/display.h"

int main (){

    char buffer [100], type[100];
    int rc, game=1;
    time_t msg_time;
    pewpew_t  zaps[2][16];
    player_data_t players[8];
    alien_data_t aliens [N_ALIENS];
 
    /* Declare and bind socket to comunicate with astronauts using the SUB/PUB patern */
    sprintf(buffer,"tcp://%s:%d",IP_ADRESS,PORT_SP);
    void *context = zmq_ctx_new ();
    void *subscriber = zmq_socket (context, ZMQ_SUB);
    rc = zmq_connect (subscriber,buffer);
    if (rc == -1){
        printf("--- ERROR ---\nBINDING TO PORT %d FAILED\n",PORT_SP);
    }
    zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE,"DISPLAY", strlen("DISPLAY"));
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

    while(1) {

        rc = zmq_recv(subscriber, type, 99, 0);
        if (rc == -1){
            printf("--- ERROR ---\nFAILED TO RECEIVE MESSAGE 1\n");
            exit(0);
        }
        
        rc = zmq_recv(subscriber, players, sizeof(player_data_t) * 8, 0);
        if (rc == -1){
            printf("--- ERROR ---\nFAILED TO RECEIVE MESSAGE 2\n");
            exit(0);
        }

        rc = zmq_recv(subscriber, aliens, sizeof(alien_data_t)*N_ALIENS, 0);
        if (rc == -1){
            printf("--- ERROR ---\nFAILED TO RECEIVE MESSAGE 3\n");
            exit(0);
        }
        rc = zmq_recv(subscriber, zaps, sizeof(pewpew_t)*2*16, 0);
        if (rc == -1){
            printf("--- ERROR ---\nFAILED TO RECEIVE MESSAGE 4\n");
            exit(0);
        }
        rc = zmq_recv(subscriber, &msg_time, sizeof(time_t), 0);
        if (rc == -1){
            printf("--- ERROR ---\nFAILED TO RECEIVE MESSAGE 5\n");
            exit(0);
        }

        rc = zmq_recv(subscriber, &game, sizeof(int), 0);
        if (rc == -1){
            printf("--- ERROR ---\nFAILED TO RECEIVE MESSAGE 6\n");
            exit(0);
        }

        if (game == 1){      
            display(players, aliens, zaps, msg_time, space, score_board);
        }else{
            break;
        }
    }
    for (int i = 0; i < 25; i++){
        mvprintw(i, 0, "                                                     ");
    }
    move(0,0);
    refresh();
    zmq_close (subscriber);
    zmq_ctx_destroy (context);
    return 0;
}