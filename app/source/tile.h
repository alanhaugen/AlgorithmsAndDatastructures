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
    int weight = 0;
    bool searched = false;

    Tile();

    void Update();
    int ManhattenDistanceToOrigin(int originX, int originY);
};

#endif
