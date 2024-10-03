#include "tile.h"
#include "main.h"

Tile::Tile()
{
}

void Tile::Update()
{
    sprite->Update();
    *moveDot->matrix.x = *sprite->matrix.x;
    *moveDot->matrix.y = *sprite->matrix.y;
    moveDot->Update();
}

void Tile::UpdateAfterPhysics()
{
}
