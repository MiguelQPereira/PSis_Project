#include "structs.h"

int main()
{
    int rc;
    remote_char_t message;
    char buffer[100];
    char resp[100];
    int score = 0;

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
        printf("%s", resp);
        sscanf(resp, "%c, %d", &message.ch, &message.id); // Save player character to the struct
        printf("Connected\nYour player character is: %c\n",message.ch);
        sleep(5);
    }
    else {
        printf("--- ERROR ---\nMAXIMUM NUMBER OF PLAYERS REACHED\n");
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
        switch (key)
        {
        case KEY_LEFT:
            // This letters correspond to the top and bottom astronauts in the display, so, they are the only ones that can move 
            // to the left or right 
            if(message.ch == 'B' || message.ch == 'D' || message.ch == 'F' || message.ch == 'H') {

                mvprintw(0,0,"%d Left arrow is pressed", n);
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

                mvprintw(0,0,"%d Right arrow is pressed", n);
                // prepare the movement message
                message.direction = LEFT;
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

                mvprintw(0,0,"%d Down arrow is pressed", n);
                // prepare the movement message
                message.direction = LEFT;
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

                mvprintw(0,0,"%d Up arrow is pressed", n);
                // prepare the movement message
                message.direction = LEFT;
                break;
            }
            // If you try to move other players than this ones in this direction you will have to try again 
            else {
                key = 0;
            }

        case ' ':
            mvprintw(0,0,"%d Zapping", n);
            // prepare ZAP message
            message.direction = ZAP;
            message.msg_type = 2; // sending zap
            break;  

        case 'q':
            mvprintw(0,0,"%d 'q' Disconnecting...", n);
            // prepare QUIT message
            message.direction = QUIT;
            message.msg_type = 3; // sending quit message 
            break;

        case 'Q':
            mvprintw(0,0,"%d 'Q' Disconnecting...", n);
            // prepare QUIT message
            message.direction = QUIT;
            message.msg_type = 3; // sending quit message 
            break;
              

        default:
            key = 0; 
            break;
        }

        //send the movement message
        if (key != 0){
            zmq_send (requester, &message, sizeof(message), 0);
            zmq_recv (requester, &score, sizeof(int), 0);
            mvprintw(10,10,"Your score: %d",score);
        }

        else {
            mvprintw(0,0,"<--- UPS ---> Try again");
        }

        
        refresh(); //Print it on to the real screen 

    }while(key != 'Q' && key != 'q');
    
    
  	endwin(); // End curses mode

    // Close socket in case of disconnect
    zmq_close (requester);
    zmq_ctx_destroy (context);

    printf ("===Left game===\nFinal Score: %d", score);

	return 0;

}