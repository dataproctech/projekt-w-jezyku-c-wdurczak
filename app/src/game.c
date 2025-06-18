#include "game.h"

int board[CELL_COUNT][CELL_COUNT];

void init_board(void) {
    for (int r = 0; r < CELL_COUNT; ++r)
        for (int c = 0; c < CELL_COUNT; ++c)
            board[r][c] = 0;
}

bool make_move(int row, int col, int player) {
    if (row < 0 || row >= CELL_COUNT || col < 0 || col >= CELL_COUNT)
        return false;
    if (board[row][col] != 0)
        return false;
    board[row][col] = player;
    return true;
}

int check_win(void) {
    for (int r = 0; r < CELL_COUNT; ++r) {
        int v = board[r][0];
        if (v != 0 && v == board[r][1] && v == board[r][2])
            return v;
    }
    for (int c = 0; c < CELL_COUNT; ++c) {
        int v = board[0][c];
        if (v != 0 && v == board[1][c] && v == board[2][c])
            return v;
    }
    int v = board[0][0];
    if (v != 0 && v == board[1][1] && v == board[2][2])
        return v;
    v = board[0][2];
    if (v != 0 && v == board[1][1] && v == board[2][0])
        return v;

    for (int r = 0; r < CELL_COUNT; ++r) {
        for (int c = 0; c < CELL_COUNT; ++c) {
            if (board[r][c] == 0) {
                return 0;
            }
        }
    }
    return -1;
}