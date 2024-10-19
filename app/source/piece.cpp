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
    iconWhite   = new Sprite(iconWhitePath, 0, 0, 0.4, 0.4);
    iconBlack   = new Sprite(iconBlackPath, 0, 0, 0.4, 0.4);
    costText    = new Text("COST: " + String(price_), 0, 0, 0.4, 0.4);
    tileBorderBlue = new Sprite("data/TileBorder-Blue.png", 0,0, 0.4, 0.4);
    tileBorderGold = new Sprite("data/TileBorder-Gold.png", 0,0, 0.4, 0.4);
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

        if (tileBorderBlue != nullptr)
        {
            *tileBorderBlue->matrix.x = *icon->matrix.x;
            *tileBorderBlue->matrix.y = *icon->matrix.y;
            *tileBorderGold->matrix.x = *icon->matrix.x;
            *tileBorderGold->matrix.y = *icon->matrix.y;
        }
    }

}
