#ifndef MOVE_H
#define MOVE_H

#include <core/components/component.h>
#include <core/components/command.h>
#include <core/application.h>
#include "tile.h"
#include "board.h"

class Piece;

class Move : public Command
{
public:
    Piece* movedPiece;
    Piece* unTransformedPiece = nullptr;
    Piece* oldPiece = nullptr;
    Tile* oldTile;
    Tile* tileToMoveTo;
    bool isPlacement = false;
    Board* gameBoard;
    Sprite* background;
    Tile* captureTile1;
    Tile* captureTile2;
    Tile* captureTile3;
    Piece* oldCapturePiece1 = nullptr;
    Piece* oldCapturePiece2 = nullptr;
    Piece* oldCapturePiece3 = nullptr;

    Move();
    Move(Piece* piece, Tile* tile, bool isPlacement_ = false, Tile *captureTile1 = nullptr, Tile *captureTile2 = nullptr, Tile *captureTile3 = nullptr);

    void Update();

    void Execute();
    void Undo();
    void Redo();
};

#endif
