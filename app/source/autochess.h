#ifndef AUTOCHESS_H
#define AUTOCHESS_H

#include <core/x-platform/scene.h>
#include "cursor.h"
#include "player.h"
#include "board.h"
#include "shop.h"

class Autochess : public IScene
{
public:
    Piece* king;
    Piece* prince;
    Piece* princess;
    Piece* shield;
    Piece* queen;
    Piece* monster;
    Piece* peasant;
    Piece* knight;
    Piece* bishop;
    Piece* stallion;
    Piece* jester;
    Piece* fence;
    Piece* hydra;
    Piece* rogue;
    Piece* cannon;
    Piece* activePiece;

    Autochess();
    Cursor* cursor;
    Board* gameBoard;
    Shop* shop;
    Tile* previousTile;

    Array<Player> players;

    bool isWhitesTurn;

    void Init();
    void Update();
    void UpdateAfterPhysics();
};

#endif
