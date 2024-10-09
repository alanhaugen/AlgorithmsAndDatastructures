#include "move.h"
#include "piece.h"

Move::Move()
{
    movedPiece = nullptr;
}

Move::Move(Piece* piece, Tile* tile, glm::vec2 position, bool isCapture_)
{
    tileToMoveTo = tile;
    oldTile = piece->currentTile;
    movedPiece = piece;
    oldPosition = glm::vec2(*piece->matrix.x, *piece->matrix.y);
    newPosition = position;
    isCapture = isCapture_;
}

void Move::Update()
{
}

void Move::Execute()
{
    movedPiece->matrix.position = glm::vec3(newPosition.x, newPosition.y, 0);
    tileToMoveTo->piece = movedPiece;
    oldTile->piece = nullptr;
}

void Move::Undo()
{
    movedPiece->matrix.position = glm::vec3(oldPosition.x, oldPosition.y, 0);
    tileToMoveTo->piece = nullptr;
    oldTile->piece = movedPiece;
}

void Move::Redo()
{
    Execute();
}
