#include "display.h"

int display (player_data_t players[8], alien_data_t aliens[N_ALIENS], pewpew_t zaps[2][16], time_t time, WINDOW * space, WINDOW * score_board){
    /* Cleans the display */
    for (int i = 1; i < 21; i++){
        mvwprintw(space, i, 1, "                    ");
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
            mvwprintw(score_board, players[i].ch - 61, 4, "%c - %d", players[i].ch, players[i].score);
        }
    }

    wrefresh(space);
    wrefresh(score_board);

    return 1;
}

int display1 (int type, void* entity, int x_old, int y_old, int zap, WINDOW * space, WINDOW * score_board){

    if (type == 0){
        alien_data_t * alien;
        alien = entity;
        mvwaddch(space, y_old, x_old, ' ');
        mvwaddch(space, alien->y, alien->x, '*');
    }
    else if (type == 1){
        player_data_t * player;
        player = entity;
        mvwaddch(space, y_old+1, x_old+1, ' ');
        mvwaddch(space, player->y+1, player->x+1, player->ch);
        mvwprintw(score_board, player->ch - 61, 4, "%c - %d", player->ch, player->score);
    }
    else if (type == 2){
        player_data_t * player;
        player = entity;
        char ch;

        if (zap == 0){
            for (int i = 1; i <= 20; i++){
                ch = (mvwinch(space, player->y+1, i) & A_CHARTEXT);
                if(ch == ' ')
                    mvwaddch(space, player->y+1, i, '-');
                else if(ch != '*' && ch != player->ch){
                    mvwaddch(space, player->y+1, i, '@');
                }
            }

        }else{
            for (int i = 1; i <= 20; i++){
                ch = (mvwinch(space, i, player->x+1) & A_CHARTEXT);
                if(ch == ' ')
                    mvwaddch(space, i, player->x+1, '|');
                else if(ch != '*' && ch != player->ch){
                    mvwaddch(space, i, player->x+1, '@');
                }
            }
        }
        mvwprintw(score_board, player->ch - 61, 4, "%c - %d", player->ch, player->score);
    }
    else if (type == 3){
        mvwaddch(space, y_old+1, x_old+1, ' ');
    }


    refresh();
    wrefresh(space);
    wrefresh(score_board);

    return 1;
}