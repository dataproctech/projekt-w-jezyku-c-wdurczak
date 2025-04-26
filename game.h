//
// Created by Wojciech Durczak on 26/04/2025.
//

#ifndef GAME_H
#define GAME_H

#include "board.h"

typedef struct {
    Board board;
    char current_player;
    int game_over;
} Game;

void game_init(Game *game);
int game_make_move(Game *game, int row, int col);
int game_check_winner(const Game *game);

#endif