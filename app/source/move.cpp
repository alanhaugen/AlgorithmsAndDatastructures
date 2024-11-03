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
    oldPiece = tileToMoveTo->piece;

    //movedPiece.Get = Set.activePiece

    //Hydra forblir på stedet, men TileMoveTo blir nullptr
    if(movedPiece->canReturnAfterCapture==true && isCapture)
    {
        tileToMoveTo->piece = nullptr;
    }
    else
    {
        tileToMoveTo->piece = movedPiece;
        oldTile->piece = nullptr;
        movedPiece->currentTile = tileToMoveTo;
    }


}

void Move::Undo()
{
    tileToMoveTo->piece = oldPiece;
    oldTile->piece = movedPiece;
    movedPiece->currentTile = oldTile;
}

void Move::Redo()
{
    Execute();
}
