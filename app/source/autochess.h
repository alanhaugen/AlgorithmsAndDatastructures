#ifndef autochess_H
#define autochess_H

#include <core/x-platform/scene.h>
#include "board.h"

class autochess : public IScene
{
public:
    autochess();
    Board* board;

    void Init();
    void Update();
    void UpdateAfterPhysics();
};

#endif
