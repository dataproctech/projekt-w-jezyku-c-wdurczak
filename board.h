//
// Created by Wojciech Durczak on 26/04/2025.
//

#ifndef BOARD_H
#define BOARD_H

#define BOARD_SIZE 3

typedef struct {
    char cells[BOARD_SIZE][BOARD_SIZE];
} Board;

void board_init(Board *board);
int board_is_full(const Board *board);

#endif