#ifndef autochess_H
#define autochess_H

#include <core/x-platform/scene.h>
#include "player.h"
#include "board.h"

class autochess : public IScene
{
public:
    autochess();
    Board* board;

    Array<Player> players;

    void Init();
    void Update();
    void UpdateAfterPhysics();
};

#endif
