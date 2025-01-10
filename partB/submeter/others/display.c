#include "display.h"

int display (player_data_t players[8], alien_data_t aliens[N_ALIENS], pewpew_t zaps[2][16], time_t time, WINDOW * space, WINDOW * score_board){
    /* Cleans the display form entities*/
    for (int i = 1; i < 21; i++){
        mvwprintw(space, i, 1, "                    ");
    }
    for (int i = 5; i < 21; i++){
        mvwprintw(score_board, i, 1, "                    ");
    }
    

    /* Puts lasers */
    for (int i=0; i<2; i++){
        for (int j = 0; j < 16; j++){

            if (i == 0 && zaps[i][j].player != -1 && difftime(time, zaps[i][j].time) < 0.5){
                mvwprintw(space, j+3, 1, "--------------------");
            }
            if (i == 1 && zaps[i][j].player != -1 && difftime(time, zaps[i][j].time) < 0.5){
                for (int z = 1; z < 21; z++){
                    mvwaddch(space, z, j+3, '|');
                }
            }
        }
    }

    /* Puts aliens */
    for (int i=0; i< N_ALIENS; i++){
        if (aliens[i].hp == 1){
            mvwaddch(space, aliens[i].y+1, aliens[i].x+1, '*');
        }
    }


    /* Puts players and score*/
    for (int i=0; i<8; i++){
        if (players[i].id != -1){
            if (difftime(time, players[i].stun)>=10)
                mvwaddch(space, players[i].y+1, players[i].x+1, players[i].ch);
            else
                mvwaddch(space, players[i].y+1, players[i].x+1, '@');
        }
        if (players[i].score != -1){
            mvwprintw(score_board, players[i].ch - 61, 4, "%c - %d   ", players[i].ch, players[i].score);
        }
    }

    wrefresh(space);
    wrefresh(score_board);

    return 1;
}