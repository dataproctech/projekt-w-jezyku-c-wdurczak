from fastapi import FastAPI, HTTPException
from models.requests.MoveRequest import MoveRequest
from models.responses.MoveResponse import MoveResponse
from game import minimax

app = FastAPI()

@app.post("/move", response_model=MoveResponse)
async def get_best_move(req: MoveRequest):
    board, player = req.board, req.player

    if len(board) != 3 or any(len(row) != 3 for row in board):
        raise HTTPException(status_code=400, detail="plansza musi mieć wymiary 3x3")
    if player not in (1, 2):
        raise HTTPException(status_code=400, detail="gracz musi być 1 lub 2")

    _, move = minimax(board, player, True)
    if move is None:
        raise HTTPException(status_code=400, detail="brak ruchów")

    return MoveResponse(row=move[0], col=move[1])