#include "move.h"
#include "piece.h"

Move::Move(Piece* piece, glm::vec2 position)
{
    movedPiece = piece;
    oldPosition = glm::vec2(*piece->matrix.x, *piece->matrix.y);
    newPosition = position;
}

void Move::Update()
{
}

void Move::Execute()
{
    movedPiece->matrix.position = glm::vec3(newPosition.x, newPosition.y, 0);
}

void Move::Undo()
{
    movedPiece->matrix.position = glm::vec3(oldPosition.x, oldPosition.y, 0);
}

void Move::Redo()
{
    Execute();
}
