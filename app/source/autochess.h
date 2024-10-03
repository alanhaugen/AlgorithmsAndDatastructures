#ifndef AUTOCHESS_H
#define AUTOCHESS_H

#include <core/x-platform/scene.h>
#include "player.h"
#include "board.h"
#include "shop.h"

class autochess : public IScene
{
public:
    autochess();
    Board* gameBoard;
    Shop* shop;

    Array<Player> players;

    void Init();
    void Update();
    void UpdateAfterPhysics();
};

#endif
