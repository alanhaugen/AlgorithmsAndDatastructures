#ifndef TILE_H
#define TILE_H

#include <core/components/component.h>
#include <core/components/sprite.h>

#include "tree.h"

class Piece;

class Tile : public Component
{
public:
    int x,y;
    Sprite* sprite;
    Sprite* moveDot;
    Sprite* attackBorder;
    Sprite* weightBorder;
    Piece* piece;
    //bool blockedSouth;
    //bool blockedNorth;
    int weight = 0;
    bool searched;
    bool visited;
    int F, G, H; // Used for A* in autochess.cpp
    Tree<Tile*>::Node* node;

    Tile();

    void Update();
    int ManhattenDistanceToOrigin(int originX, int originY);
};

#endif
