#include <ncurses.h>
#include "structs.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>  
#include <ctype.h> 
#include <stdlib.h>
#include <zmq.h>
#include <stdio.h>
#include <string.h>

int main()
{
    int rc;
    char buffer[100];
    char resp[100];

    /* Declare and bind socket to comunicate with astronauts using the REP/REQ patern */
    sprintf(buffer,"tcp://%s:%d",IP_ADRESS,PORT_RR);
    void *context = zmq_ctx_new ();
    void *requester = zmq_socket (context, ZMQ_REQ);
    rc = zmq_connect (requester,buffer);

    if (rc == -1){
        printf("--- ERROR ---\nBinding to port %d failed\n",PORT_RR);
    }


    // Send connection message
    remote_char_t message;
    message.msg_type = 0;
    printf("Connecting...\n");
    zmq_send (requester, &message, sizeof(message), 0);
    zmq_recv (requester, &resp, sizeof(resp), 0);
    if(strlen(resp) < 1) {
        strcpy(message.ch,resp); // Save player character to the struct
        printf("Connected\n");
    }
    else {
        printf("--- ERROR ---\nMAXIMUM NUMBER OF PLAYERS REACHED\n"); 
    }
    


	initscr();			/* Start curses mode 		*/
	cbreak();				/* Line buffering disabled	*/
	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	noecho();			/* Don't echo() while we do getch */

    int n = 0;

    //TODO_9
    // prepare the movement message
    m.msg_type = 1;
    //m.ch = ch;
    
    int key;
    do
    {
    	key = getch();		
        n++;
        switch (key)
        {
        case KEY_LEFT:
            mvprintw(0,0,"%d Left arrow is pressed", n);
            //TODO_9
            // prepare the movement message
           m.direction = LEFT;
            break;
        case KEY_RIGHT:
            mvprintw(0,0,"%d Right arrow is pressed", n);
            //TODO_9
            // prepare the movement message
            m.direction = RIGHT;
            break;
        case KEY_DOWN:
            mvprintw(0,0,"%d Down arrow is pressed", n);
            //TODO_9
            // prepare the movement message
           m.direction = DOWN;
            break;
        case KEY_UP:
            mvprintw(0,0,"%d :Up arrow is pressed", n);
            //TODO_9
            // prepare the movement message
            m.direction = UP;
            break;

        default:
            key = 'x'; 
            break;
        }

        //TODO_10
        //send the movement message
         if (key != 'x'){
            zmq_send (requester, &m, sizeof(m), 0);
            zmq_recv (requester, &res, sizeof(res), 0);
        }
        refresh();			/* Print it on to the real screen */
    }while(key != 27);
    
    
  	endwin();			/* End curses mode		  */

	return 0;
}