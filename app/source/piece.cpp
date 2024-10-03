#include "piece.h"

Piece::Piece(String name_,
             String iconPath,
             String description_,
             int price_,
             int range_)
{
    name = name_;
    icon = new Sprite(iconPath);
    description = description_;
    price = price_;
    range = range_;

    isActive = false;
    isFlying = false;
}

void Piece::Update()
{
}

void Piece::UpdateAfterPhysics()
{
}

