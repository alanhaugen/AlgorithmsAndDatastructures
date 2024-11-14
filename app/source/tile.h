#ifndef TILE_H
#define TILE_H

#include <core/components/component.h>
#include <core/components/sprite.h>

class Piece;

class Tile : public Component
{
public:
    int x,y;
    Sprite* sprite;
    Sprite* moveDot;
    Sprite* attackBorder;
    Piece* piece;
    //bool blockedSouth;
    //bool blockedNorth;
    int weight = 0;
    bool searched = false;

    Tile();

    void Update();
    int ManhattenDistanceToOrigin(int originX, int originY);
};

#endif
