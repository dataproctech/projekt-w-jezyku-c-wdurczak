//
// Created by Wojciech Durczak on 26/04/2025.
//
#include "board.h"

void board_init(Board *board) {
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            board->cells[i][j] = ' ';
}

int board_is_full(const Board *board) {
    for (int i = 0; i <BOARD_SIZE; ++i)
        for (int j = 0; j <BOARD_SIZE; ++j)
            if (board->cells[i][j]==' ')
                return 0;
    return 1;
}