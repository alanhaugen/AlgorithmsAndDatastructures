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
    Autochess();
    Cursor* cursor;
    Board* gameBoard;
    Shop* shop;

    Piece* activePiece = nullptr;

    Array<Player> players;

    bool isWhitesTurn;

    void Init();
    void Update();
};

#endif
