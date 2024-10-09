#ifndef MOVE_H
#define MOVE_H

#include <core/components/component.h>
#include <core/components/command.h>
#include "tile.h"

class Piece;

class Move : public Command
{
public:
    Piece* movedPiece;
    Tile* oldTile;
    Tile* tileToMoveTo;
    glm::vec2 newPosition;
    glm::vec2 oldPosition;
    bool isCapture;

    Move();
    Move(Piece* piece, Tile* tile, glm::vec2 position, bool isCapture_ = false);

    void Update();

    void Execute();
    void Undo();
    void Redo();
};

#endif
