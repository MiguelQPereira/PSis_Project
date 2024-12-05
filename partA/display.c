#include <ncurses.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>  
#include <stdlib.h>
#include <zmq.h>
#include <assert.h>

#include "structs.h"


int display (){

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

    refresh();
    wrefresh(space);
    wrefresh(score_board);

    sleep(100);
    endwin();			/* Termina o modo curses */
    return 1;
}

int main(){

    server_data_t players[8];
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

    players[0].id = 1;
    players[1].id = 1;

    display();
    return 1;
}
