#include "move.h"
#include "piece.h"

Move::Move()
{
    movedPiece = nullptr;
}

Move::Move(Piece* piece, Tile* tile, bool isPlacement_, Tile* captureTile1_, Tile* captureTile2_, Tile* captureTile3_)
{
    isPlacement = isPlacement_;
    tileToMoveTo = tile;
    oldTile = piece->currentTile;
    movedPiece = piece;

    captureTile1 = captureTile1_;
    captureTile2 = captureTile2_;
    captureTile3 = captureTile3_;

    if (captureTile1 != nullptr)
    {
        oldCapturePiece1 = captureTile1->piece;

        if (captureTile2 != nullptr)
        {
            oldCapturePiece2 = captureTile2->piece;

            if (oldCapturePiece3 != nullptr)
            {
                oldCapturePiece3 = captureTile3->piece;
            }
        }

    }
}

void Move::Update()
{
}

void Move::Execute()
{
    if (captureTile1 != nullptr)
    {
        captureTile1->piece = nullptr;

        if (captureTile2 != nullptr)
        {
            captureTile2->piece = nullptr;

            if (captureTile3 != nullptr)
            {
                captureTile3->piece = nullptr;
            }
        }
    }

    oldPiece = tileToMoveTo->piece;

    if(tileToMoveTo->piece != movedPiece && movedPiece->canReturnAfterCapture == true && captureTile1 != nullptr)
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

    if (oldCapturePiece1 != nullptr)
    {
        captureTile1->piece = oldCapturePiece1;

        if (oldCapturePiece2 != nullptr)
        {
            captureTile2->piece = oldCapturePiece2;

            if (oldCapturePiece3 != nullptr)
            {
                captureTile3->piece = oldCapturePiece3;
            }
        }
    }
}

void Move::Redo()
{
    Execute();
}
