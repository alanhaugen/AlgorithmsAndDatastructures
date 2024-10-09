#include "move.h"
#include "piece.h"

Move::Move()
{
    movedPiece = nullptr;
}

Move::Move(Piece* piece, Tile* tile, bool isCapture_)
{
    tileToMoveTo = tile;
    oldTile = piece->currentTile;
    movedPiece = piece;
    isCapture = isCapture_;
}

void Move::Update()
{
}

void Move::Execute()
{
    tileToMoveTo->piece = movedPiece;
    oldTile->piece = nullptr;
    movedPiece->currentTile = tileToMoveTo;
}

void Move::Undo()
{
    tileToMoveTo->piece = nullptr;
    oldTile->piece = movedPiece;
    movedPiece->currentTile = oldTile;
}

void Move::Redo()
{
    Execute();
}
