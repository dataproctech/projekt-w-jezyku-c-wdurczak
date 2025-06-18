from pydantic import BaseModel
from typing import List

class MoveRequest(BaseModel):
    board: List[List[int]]
    player: int

