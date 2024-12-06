#include "display.h"

int display (int type, void* entity, int x_old, int y_old, int zap, WINDOW * space, WINDOW * score_board){

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

    return 1;
}

