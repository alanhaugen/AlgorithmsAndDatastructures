#include "piece.h"

Piece::Piece()
{
}

Piece::Piece(String name_,
             String iconWhitePath,
             String iconBlackPath,
             String description_,
             int price_,
             int nobility_)
{
    name = name_;
    iconWhite   = new Sprite(iconWhitePath, 0, 0, 0.25, 0.25);
    iconBlack   = new Sprite(iconBlackPath, 0, 0, 0.25, 0.25);
    costText    = new Text("COST: " + String(price_), 0, 0, 0.25, 0.25);
    description = description_;
    price       = price_;
    nobility    = nobility_;

    icon = iconWhite;
}

void Piece::Update()
{
    if (icon != nullptr)
    {
        icon->Update();
    }
}
