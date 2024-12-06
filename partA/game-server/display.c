#include "display.h"

int display (int type, void* entity, int x_old, int y_old, int zap, WINDOW * space, WINDOW * score_board){

    initscr();		    	
	cbreak();				
    keypad(stdscr, TRUE);   
	noecho();

    /* creates the windows and draws the borders of the outer-space and the score board 
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
    mvaddch(21, 0, '0');*/


    if (type == 0){
        alien_data_t * alien;
        alien = entity;
        mvwaddch(space, y_old, x_old, ' ');
        mvwaddch(space, alien->y, alien->x, '*');
    }
    else if (type == 1){
        player_data_t * player;
        player = entity;
        mvwaddch(space, y_old, x_old, ' ');
        mvwaddch(space, player->y, player->x, player->ch);
        mvwprintw(score_board, player->ch - 60, 3, "%c - %d", player->ch, player->score);
    }
    else if (type == 2){
        return 0;
    }
    else if (type == 3){
        mvwaddch(space, y_old, x_old, ' ');
    }


    refresh();
    wrefresh(space);
    wrefresh(score_board);

    endwin();			/* Termina o modo curses */
    return 1;
}

