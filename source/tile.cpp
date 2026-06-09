#include "tile.h"
#include "main.h"
#include "piece.h"

Tile::Tile()
{
    piece  = nullptr;
    F = 0;
    searched = false;
    visited  = false;
    node = nullptr;
}

void Tile::Update(float dt)
{
    sprite->Update(dt);

    *moveDot->matrix.x = *sprite->matrix.x;
    *moveDot->matrix.y = *sprite->matrix.y;
    moveDot->Update(dt);

    *attackBorder->matrix.x = *sprite->matrix.x;
    *attackBorder->matrix.y = *sprite->matrix.y;
    attackBorder->Update(dt);

    *weightBorder->matrix.x = *sprite->matrix.x;
    *weightBorder->matrix.y = *sprite->matrix.y;
    weightBorder->Update(dt);

    *weightBorderWhite->matrix.x = *sprite->matrix.x;
    *weightBorderWhite->matrix.y = *sprite->matrix.y;
    weightBorderWhite->Update(dt);

    if (piece != nullptr)
    {
        if (piece->isCurrentlyInAnimation == false)
        {
            *piece->icon->matrix.x = *sprite->matrix.x;
            *piece->icon->matrix.y = *sprite->matrix.y;
        }

        piece->Update(dt);
    }
}

void Tile::UpdateAfterPhysics()
{
}

int Tile::ManhattenDistanceToOrigin(int originX, int originY)
{
    return abs(x - originX) + abs(y - originY);
}
