#include "tile.h"
#include "main.h"
#include "piece.h"

Tile::Tile()
{
    piece  = nullptr;
}

void Tile::Update()
{
    sprite->Update();
    *moveDot->matrix.x = *sprite->matrix.x;
    *moveDot->matrix.y = *sprite->matrix.y;
    moveDot->Update();

    *attackBorder->matrix.x = *sprite->matrix.x;
    *attackBorder->matrix.y = *sprite->matrix.y;
    attackBorder->Update();

    if (piece != nullptr)
    {
        *piece->icon->matrix.x = *sprite->matrix.x;
        *piece->icon->matrix.y = *sprite->matrix.y;
        piece->Update();
    }
}

int Tile::ManhattenDistanceToOrigin(int originX, int originY)
{
    return abs(x - originX) + abs(y - originY);
}
