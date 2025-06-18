#ifndef API_CLIENT_H
#define API_CLIENT_H

#include <stdbool.h>

bool get_best_move_api(int player, int board[3][3], int *row, int *col);

#endif