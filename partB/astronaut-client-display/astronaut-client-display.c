#include "../others/structs.h"
#include "../others/display.h"


int client_game = 1; // Variable to control the game state of the client

void * show_display(){

    char buffer [100], type[100];
    int rc, game = 1;
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

        if (game == 1 && client_game == 1){   
            display(players, aliens, zaps, msg_time, space, score_board);
        }else{
            break;
        }

        
    }
    mvprintw(0, 0, "Server Closed. Press a q/Q                                       ");
    for (int i = 1; i < 25; i++){
        mvprintw(i, 0, "                                                     ");
    }
    move(0,0);
    refresh();
    zmq_close (subscriber);
    zmq_ctx_destroy (context);
}
    
int main(){


    int rc;
    remote_char_t message;
    char buffer[100];
    char resp[100];
    int score = 0, n_resp = 0;

    /* Declare and bind socket to comunicate with astronauts using the REP/REQ patern */
    sprintf(buffer,"tcp://%s:%d",IP_ADRESS,PORT_RR);
    void *context = zmq_ctx_new ();
    void *requester = zmq_socket (context, ZMQ_REQ);
    rc = zmq_connect (requester,buffer);

    if (rc == -1){
        printf("--- ERROR ---\nBINDING TO PORT %d FAILED\n",PORT_RR);
    }


    // Send connection message
    message.msg_type = 0;
    printf("Connecting...\n");
    rc = zmq_send (requester, &message, sizeof(message), 0);
    if (rc == -1){
            printf("--- ERROR ---\nFAILED TO SEND MESSAGE\n");
            exit(0);
        }
    rc = zmq_recv (requester, &resp, sizeof(resp), 0);
    if (rc == -1){
            printf("--- ERROR ---\nFAILED TO RECEIVE MESSAGE\n");
            exit(0);
        }
    if(strcmp(resp, "-1") != 0) {
        sscanf(resp, "%c, %d", &message.ch, &message.id); // Save player character to the struct
        printf("Connected\nYour player character is: %c\n",message.ch);
        sleep(5);
    }
    else {
        printf("--- ERROR ---\nMAXIMUM NUMBER OF PLAYERS REACHED\n");
        exit(1);
    }

    long int thread_display_id;
    int check;
    thread_display_id = 0;

    // Create the thread for the dissplay
    check = pthread_create(&thread_display_id, NULL, show_display, NULL);
    if (check != 0) {
        printf("--- ERROR ---\nCOULDN'T CREATE DISPLAY THREAD");
        exit(1);
    }
    
    // prepare the movement message
    message.msg_type = 1;

	initscr();			/* Start curses mode 		*/
	cbreak();				/* Line buffering disabled	*/
	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	noecho();			/* Don't echo() while we do getch */

    int n = 0; // Count the keys pressed
    
    int key;
    do
    {
    	key = getch();		
        n++;
        switch (key){
            case KEY_LEFT:
                // This letters correspond to the top and bottom astronauts in the display, so, they are the only ones that can move 
                // to the left or right 
                if(message.ch == 'B' || message.ch == 'D' || message.ch == 'F' || message.ch == 'H') {
                    message.msg_type = 1;
                    // prepare the movement message
                    message.direction = LEFT;
                    break;
                }
                // If you try to move other players than this ones in this direction you will have to try again 
                else {
                    key = 0;
                }
                    
            case KEY_RIGHT:
                // This letters correspond to the top and bottom astronauts in the display, so, they are the only ones that can move 
                // to the left or right
                if(message.ch == 'B' || message.ch == 'D' || message.ch == 'F' || message.ch == 'H') {
                    message.msg_type = 1;
                    // prepare the movement message
                    message.direction = RIGHT;
                    break;
                }
                // If you try to move other players than this ones in this direction you will have to try again 
                else {
                    key = 0;
                }
            case KEY_DOWN:
                // This letters correspond to the left and right astronauts in the display, so, they are the only ones that can move 
                // up and down
                if(message.ch == 'A' || message.ch == 'C' || message.ch == 'E' || message.ch == 'G') {
                    message.msg_type = 1;
                    // prepare the movement message
                    message.direction = DOWN;
                    break;
                }
                // If you try to move other players than this ones in this direction you will have to try again 
                else {
                    key = 0;
                }
            case KEY_UP:
                // This letters correspond to the left and right astronauts in the display, so, they are the only ones that can move 
                // up and down
                if(message.ch == 'A' || message.ch == 'C' || message.ch == 'E' || message.ch == 'G') {
                    message.msg_type = 1;
                    // prepare the movement message
                    message.direction = UP;
                    break;
                }
                // If you try to move other players than this ones in this direction you will have to try again 
                else {
                    key = 0;
                }

            case ' ':
                // prepare ZAP message
                message.msg_type = 2; // sending zap
                break;  

            case 'q':
                client_game = 0;
                // prepare QUIT message
                message.msg_type = 3; // sending quit message 
                break;

            case 'Q':
                client_game = 0;
                // prepare QUIT message
                message.msg_type = 3; // sending quit message
                break;

            default:
                key = 0; 
                break;
        }

        //send the movement message
        if (key != 0){
            rc = zmq_send (requester, &message, sizeof(message), 0);
            if (rc == -1){
                mvprintw(5,0,"--- ERROR ---\nFAILED TO SEND MESSAGE");
                exit(0);
            }
            rc = zmq_recv (requester, &n_resp, sizeof(int), 0);
            if (rc == -1){
                mvprintw(10,0,"--- ERROR ---\nFAILED TO RECEIVE MESSAGE");
                exit(0);
            }
            if (n_resp == -1 || n_resp == -2){ //Check if the game ended
                key = 'q';
            }
            else{
                score = n_resp;
            }
        }
 

    }while(key != 'Q' && key != 'q');
 
    // Wait for thread to finish
    pthread_join(thread_display_id, NULL);
    
    endwin(); // End curses mode

    // Close socket in case of disconnect
    zmq_close (requester);
    zmq_ctx_destroy (context);

    if(n_resp == -1){
        printf ("You won!!!\nFinal Score: %d\n", score);
    }else if(n_resp == -2){
        printf ("Game ended\nFinal Score: %d\n", score);
    }else
        printf ("===Left game===\nFinal Score: %d\n", score);
 

    return 0;
    
}
    
