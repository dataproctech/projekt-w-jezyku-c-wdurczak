#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#define CELL_COUNT 3

extern int board[CELL_COUNT][CELL_COUNT];

void init_board(void);
bool make_move(int row, int col, int player);
int check_win(void);

#endif
