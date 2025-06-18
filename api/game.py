from typing import List, Optional, Tuple


def check_win(board: List[List[int]]) -> int:
    for i in range(3):
        if board[i][0] and board[i][0] == board[i][1] == board[i][2]:
            return board[i][0]
        if board[0][i] and board[0][i] == board[1][i] == board[2][i]:
            return board[0][i]
    if board[0][0] and board[0][0] == board[1][1] == board[2][2]:
        return board[0][0]
    if board[0][2] and board[0][2] == board[1][1] == board[2][0]:
        return board[0][2]
    for row in board:
        if 0 in row:
            return 0
    return -1


def minimax(board: List[List[int]], player: int, maximizing: bool) -> Tuple[int, Optional[Tuple[int,int]]]:
    result = check_win(board)
    if result == player:
        return 1, None
    if result == -1:
        return 0, None
    if result != 0:
        return -1, None

    best_score = -2 if maximizing else 2
    best_move: Optional[Tuple[int,int]] = None
    opponent = 1 if player == 2 else 2

    for r in range(3):
        for c in range(3):
            if board[r][c] == 0:
                board[r][c] = player if maximizing else opponent
                score, _ = minimax(board, player, not maximizing)
                board[r][c] = 0
                if maximizing and score > best_score:
                    best_score, best_move = score, (r, c)
                if not maximizing and score < best_score:
                    best_score, best_move = score, (r, c)
    return best_score, best_move