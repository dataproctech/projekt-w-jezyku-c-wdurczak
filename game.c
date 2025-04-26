//
// Created by Wojciech Durczak on 26/04/2025.
//

#include "game.h"

void game_init(Game *game) {
    board_init(&game->board);
    game->current_player = 'X';
    game->game_over = 0;
}

int game_make_move(Game *game, int row, int col) {
    if (row < 0|| row >=BOARD_SIZE || col < 0 || col >= BOARD_SIZE)
        return 0;
    if (game->board.cells[row][col] != ' '|| game->game_over)
        return 0;
    game->board.cells[row][col] =game->current_player;
    return 1;
}

int game_check_winner(const Game *game) {
    char p =game->current_player;
    Board *b =(Board *)&game->board;
    for (int i = 0; i<BOARD_SIZE; ++i)
        if ((b->cells[i][0] == p&& b->cells[i][1] ==p && b->cells[i][2] == p) ||
            (b->cells[0][i] == p && b->cells[1][i] == p && b->cells[2][i] == p))
            return 1;
    if ((b->cells[0][0] ==p && b->cells[1][1] == p && b->cells[2][2] == p) ||
        (b->cells[0][2] == p && b->cells[1][1] == p && b->cells[2][0] == p))
        return 1;
    return 0;
}