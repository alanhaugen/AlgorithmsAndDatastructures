#ifndef TILE_H
#define TILE_H

#include <core/components/component.h>
#include <core/components/sprite.h>

class Tile : public Component
{
public:
    int x,y;
    Sprite* sprite;

    Tile();

    void Update();
    void UpdateAfterPhysics();
};

#endif
