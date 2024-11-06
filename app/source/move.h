#ifndef MOVE_H
#define MOVE_H

#include <core/components/component.h>
#include <core/components/command.h>
#include "tile.h"
#include "board.h"

class Piece;

class Move : public Command
{
public:
    Piece* movedPiece;
    Piece* oldPiece = nullptr;
    Tile* oldTile;
    Tile* tileToMoveTo;
    bool isCapture;
    bool isPlacement = false;
    Board* gameBoard;
    Sprite* background;

    Move();
    Move(Piece* piece, Tile* tile, bool isCapture_ = false, bool isPlacement_ = false);

    void Update();

    void Execute();
    void Undo();
    void Redo();
};

#endif
