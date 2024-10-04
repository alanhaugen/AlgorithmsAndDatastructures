#ifndef TILE_H
#define TILE_H

#include <core/components/component.h>
#include <core/components/sprite.h>
#include "piece.h"

class Tile : public Component
{
public:
    int x,y;
    Sprite* sprite;
    Sprite* moveDot;
    Piece* piece;
    bool blockedSouth;
    bool blockedNorth;

    Tile();

    void Update();
};

#endif
