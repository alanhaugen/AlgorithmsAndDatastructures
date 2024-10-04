#include "tile.h"
#include "main.h"

Tile::Tile()
{
    piece = nullptr;
}

void Tile::Update()
{
    sprite->Update();
    *moveDot->matrix.x = *sprite->matrix.x;
    *moveDot->matrix.y = *sprite->matrix.y;
    moveDot->Update();

    if (piece != nullptr)
    {
        *piece->icon->matrix.x = *sprite->matrix.x;
        *piece->icon->matrix.y = *sprite->matrix.y;
        piece->Update();
    }
}
