#include "piece.h"

Piece::Piece()
{
}

Piece::Piece(String name_,
             String iconPath,
             String description_,
             int price_,
             int nobility_)
{
    name = name_;
    icon = new Sprite(iconPath, 0, 0, 0.25, 0.25);
    description = description_;
    price    = price_;
    nobility = nobility_;
}

void Piece::Update()
{
    if (icon != nullptr)
    {
        icon->Update();
    }
}
