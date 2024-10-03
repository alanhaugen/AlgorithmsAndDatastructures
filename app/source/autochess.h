#ifndef AUTOCHESS_H
#define AUTOCHESS_H

#include <core/x-platform/scene.h>
#include "player.h"
#include "board.h"
#include "shop.h"

class Autochess : public IScene
{
public:
    Autochess();
    Board* gameBoard;
    Shop* shop;

    Array<Player> players;

    void Init();
    void Update();
    void UpdateAfterPhysics();
};

#endif
