#ifndef BOARD_H
#define BOARD_H

#include <core/components/component.h>
#include <core/components/sprite.h>
#include <core/components/camera.h>
#include "tile.h"

class Board : public Component
{
public:
    Sprite* background;
    Sprite* cursor;
    Array<Tile> tiles;
    Camera* cam;
    Board();

    void Update();
    void UpdateAfterPhysics();
};

#endif
