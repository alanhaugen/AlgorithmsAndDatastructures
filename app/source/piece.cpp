#include "piece.h"

Piece::Piece()
{
}

Piece::Piece(String name_,
             String iconWhitePath,
             String iconBlackPath,
             String description_,
             int price_,
             int nobility_,
             int range,
             bool isJumping_,
             bool canReturnAfterCapture)
{
    name = name_;

    backgroundCard = new Sprite("data/Card-Standard.png", 0,0, 2.2 * 1.5, 3.1 * 1.5);

    iconWhite   = new Sprite(iconWhitePath, 0, 0, 0.4, 0.4);
    iconBlack   = new Sprite(iconBlackPath, 0, 0, 0.4, 0.4);

    buyText   = new Text("Click to buy", 0, 0, 0.4 * 1.5, 0.4 * 1.5);

    nameText  = new Text(name_, 0, 0, 0.4 * 1.5, 0.4 * 1.5);
    movementTypeText  = new Text(isJumping_ ? String("Jumping") : String("Grounded"), 0, 0, 0.4 * 1.5, 0.4 * 1.5);
    movementText  = new Text("Range: " + String(range), 0, 0, 0.4 * 1.5, 0.4 * 1.5);
    descriptionText    = new Text(description_, 0, 0, 0.4 * 1.5, 0.4 * 1.5);
    nobilityText    = new Text("Nobility: " + String(nobility_), 0, 0, 0.4 * 1.5, 0.4 * 1.5);
    costText    = new Text("COST: " + String(price_), 0, 0, 0.4 * 1.5, 0.4 * 1.5);

    tileBorderBlue = new Sprite("data/TileBorder-Blue.png", 0,0, 0.4, 0.4);
    tileBorderGold = new Sprite("data/TileBorder-Gold.png", 0,0, 0.4, 0.4);
    description = description_;
    price       = price_;
    nobility    = nobility_;

    isJumping = isJumping_;

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
