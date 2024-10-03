#include "piece.h"

Piece::Piece()
{
}

Piece::Piece(String name_,
             String iconPath,
             String description_,
             int price_,
             int range_)
{
    name = name_;
    icon = new Sprite(iconPath, 0, 0, 0.25, 0.25);
    description = description_;
    price = price_;
    range = range_;

    isActive = false;
    isFlying = false;
}

void Piece::Update()
{
    icon->Update();
}

void Piece::UpdateAfterPhysics()
{
}

