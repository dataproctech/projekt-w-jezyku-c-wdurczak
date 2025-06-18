from pydantic import BaseModel

class MoveResponse(BaseModel):
    row: int
    col: int