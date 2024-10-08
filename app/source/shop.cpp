#include "shop.h"

Shop::Shop()
{
    FillShopItems();
}

Piece* Shop::CreateRandomPiece()
{
    int randomNumber = random.RandomRange(0, PIECE_TYPES_QUANTITY - 1);

    Piece* piece = nullptr;

    switch(randomNumber)
    {
    case 0:
        piece = new Piece("King",
                         "data/Piece-WhiteKing.png",
                         "data/Piece-BlackKing.png",
                         "Moves like a king in chess. Can move 1 tile in any direction.",
                         200,
                         10);

        for (int i = 1; i <= 1; i++)
        {
            piece->movePattern.Add(glm::vec2(i,0));
            piece->movePattern.Add(glm::vec2(-i,0));
            piece->movePattern.Add(glm::vec2(0,i));
            piece->movePattern.Add(glm::vec2(0,-i));

            piece->movePattern.Add(glm::vec2(i,i));
            piece->movePattern.Add(glm::vec2(i,-i));
            piece->movePattern.Add(glm::vec2(-i,i));
            piece->movePattern.Add(glm::vec2(-i,-i));
        }

        break;
    case 1:
        piece = new Piece("Prince",
                         "data/Piece-WhitePrince.png",
                         "data/Piece-BlackPrince.png",
                         "Can move 4 tiles forwards/back/left/right, then attack left/right diagonal. Can jump over fences.",
                         90,
                         6);

        piece->isJumping = true;

        // TODO: Add attack after move phase
        for (int i = 1; i <= 4; i++)
        {
            piece->movePattern.Add(glm::vec2(i,0));
            piece->movePattern.Add(glm::vec2(-i,0));
            piece->movePattern.Add(glm::vec2(0,i));
            piece->movePattern.Add(glm::vec2(0,-i));
        }

        break;
    case 2:
        piece = new Piece("Princess",
                         "data/Piece-WhitePrincess.png",
                         "data/Piece-BlackPrincess.png",
                         "Moves like a queen in chess. Can move 3 tiles in any direction. Transformer. Can acquire the qualities of adjacent friendly pieces at will.",
                         120,
                         8);

        // TODO: Add special ability
        for (int i = 1; i <= 10; i++)
        {
            piece->movePattern.Add(glm::vec2(i,0));
            piece->movePattern.Add(glm::vec2(-i,0));
            piece->movePattern.Add(glm::vec2(0,i));
            piece->movePattern.Add(glm::vec2(0,-i));

            piece->movePattern.Add(glm::vec2(i,i));
            piece->movePattern.Add(glm::vec2(i,-i));
            piece->movePattern.Add(glm::vec2(-i,i));
            piece->movePattern.Add(glm::vec2(-i,-i));
        }

        for (int y = 1; y <= 3; y++)
        {
            for (int x = 1; x <= 3; x++)
            {
                piece->movePattern.Add(glm::vec2(x,0));
                piece->movePattern.Add(glm::vec2(0,y));
                piece->movePattern.Add(glm::vec2(-x,0));
                piece->movePattern.Add(glm::vec2(0,-y));
                piece->movePattern.Add(glm::vec2(x,y));
                piece->movePattern.Add(glm::vec2(-x,y));
                piece->movePattern.Add(glm::vec2(x,-y));
                piece->movePattern.Add(glm::vec2(-x,-y));
            }
        }

        break;
    case 3:
        piece = new Piece("Shield Man",
                         "data/Piece-WhiteShield.png",
                         "data/Piece-BlackShield.png",
                         "Can move 1 tile forward or 1 tile sideways. This piece cannot capture other pieces. The tile in front will become heavy.",
                         50,
                         1);

        piece->movePattern.Add(glm::vec2(0, 1));
        piece->movePattern.Add(glm::vec2(1, 0));
        piece->movePattern.Add(glm::vec2(-1, 0));

        break;
    case 4:
        piece = new Piece("Queen",
                         "data/Piece-WhiteQueen.png",
                         "data/Piece-BlackQueen.png",
                         "Moves like a queen in chess.",
                         150,
                         5);

        for (int i = 1; i <= 10; i++)
        {
            piece->movePattern.Add(glm::vec2(i,0));
            piece->movePattern.Add(glm::vec2(-i,0));
            piece->movePattern.Add(glm::vec2(0,i));
            piece->movePattern.Add(glm::vec2(0,-i));

            piece->movePattern.Add(glm::vec2(i,i));
            piece->movePattern.Add(glm::vec2(i,-i));
            piece->movePattern.Add(glm::vec2(-i,i));
            piece->movePattern.Add(glm::vec2(-i,-i));
        }

        break;
    case 5:
        piece = new Piece("Monster",
                         "data/Piece-WhiteMonster.png",
                         "data/Piece-BlackMonster.png",
                         "Can move into any adjacent square for 5 tiles.",
                         150,
                         0);

        // TODO: Is flying?
        piece->range = 5;

        for (int y = 1; y <= 5; y++)
        {
            for (int x = 1; x <= 5; x++)
            {
                piece->movePattern.Add(glm::vec2(x,0));
                piece->movePattern.Add(glm::vec2(0,y));
                piece->movePattern.Add(glm::vec2(-x,0));
                piece->movePattern.Add(glm::vec2(0,-y));
                piece->movePattern.Add(glm::vec2(x,y));
                piece->movePattern.Add(glm::vec2(-x,y));
                piece->movePattern.Add(glm::vec2(x,-y));
                piece->movePattern.Add(glm::vec2(-x,-y));
            }
        }

        break;
    case 6:
        piece = new Piece("Peasant",
                         "data/Piece-WhitePeasant.png",
                         "data/Piece-BlackPeasant.png",
                         "Only move forward by 1 space, can capture if there is an opponent piece on that space.",
                         20,
                         0);

        piece->movePattern.Add(glm::vec2(0,1));

        break;
    case 7:
        piece = new Piece("Knight",
                         "data/Piece-WhiteRook.png",
                         "data/Piece-BlackRook.png",
                          "Moves like a rook, but only 5 tiles forwards (or backwards or ot the side)",
                          50,
                          2);

        for (int i = 1; i <= 5; i++)
        {
            piece->movePattern.Add(glm::vec2(i,0));
            piece->movePattern.Add(glm::vec2(-i,0));
            piece->movePattern.Add(glm::vec2(0,i));
            piece->movePattern.Add(glm::vec2(0,-i));
        }

        break;
    case 8:
        piece = new Piece("Bishop",
                          "data/Piece-WhiteBishop.png",
                          "data/Piece-BlackBishop.png",
                          "Moves like a bishop. Can move unlimited amount of spaces diagonally in any direction.",
                          80,
                          4);

        for (int i = 1; i <= 10; i++)
        {
            piece->movePattern.Add(glm::vec2(i,i));
            piece->movePattern.Add(glm::vec2(i,-i));
            piece->movePattern.Add(glm::vec2(-i,i));
            piece->movePattern.Add(glm::vec2(-i,-i));
        }

        break;
    case 9:
        piece = new Piece("Stallion",
                          "data/Piece-WhiteStallion.png",
                          "data/Piece-BlackStallion.png",
                          "Moves like a knight in chess. Either two steps forward and one to the side, or one step forward and two to the side. Can jump over fences.",
                          60,
                          1);

        piece->isJumping = true;
        piece->movePattern.Add(glm::vec2(1,2));
        piece->movePattern.Add(glm::vec2(1,-2));
        piece->movePattern.Add(glm::vec2(-1,-2));
        piece->movePattern.Add(glm::vec2(-1,2));
        piece->movePattern.Add(glm::vec2(2,1));
        piece->movePattern.Add(glm::vec2(2,-1));
        piece->movePattern.Add(glm::vec2(-2,1));
        piece->movePattern.Add(glm::vec2(-2,-1));

        break;
    case 10:
        piece = new Piece("Jester",
                          "data/Piece-WhiteJester.png",
                          "data/Piece-BlackJester.png",
                          "Moves diagonally 2 spaces in any direction.",
                          75,
                          3);

        for (int i = 1; i <= 2; i++)
        {
            piece->movePattern.Add(glm::vec2(i,i));
            piece->movePattern.Add(glm::vec2(i,-i));
            piece->movePattern.Add(glm::vec2(-i,i));
            piece->movePattern.Add(glm::vec2(-i,-i));
        }

        break;
    case 11:
        piece = new Piece("Fence",
                          "data/Piece-WhiteFence.png",
                          "data/Piece-BlackFence.png",
                          "Can be placed on the edge of tiles, is 3 spaces long. Blocks non-jumping pieces from passing. CAn only be placed horizontally.",
                          40,
                          0);

        for (int i = 1; i <= 10; i++)
        {
            piece->movePattern.Add(glm::vec2(i,0));
            piece->movePattern.Add(glm::vec2(-i,0));
        }

        break;
    case 12:
        piece = new Piece("Hydra",
                          "data/Piece-WhiteHydra.png",
                          "data/Piece-BlackHydra.png",
                          "Can only move 1 space at the time. Can attack up to 3 adjacent enemies.",
                          180,
                          1);

        // TODO: Add special ability

        for (int i = 1; i <= 1; i++)
        {
            piece->movePattern.Add(glm::vec2(i,0));
            piece->movePattern.Add(glm::vec2(-i,0));
            piece->movePattern.Add(glm::vec2(0,i));
            piece->movePattern.Add(glm::vec2(0,-i));

            piece->movePattern.Add(glm::vec2(i,i));
            piece->movePattern.Add(glm::vec2(i,-i));
            piece->movePattern.Add(glm::vec2(-i,i));
            piece->movePattern.Add(glm::vec2(-i,-i));
        }

        break;
    case 13:
        piece = new Piece("Rogue",
                          "data/Piece-WhiteRogue.png",
                          "data/Piece-BlackRogue.png",
                          "Can move 2 tiles in any direction. If the rogue eliminates an enemy piece, the rogue moves back to its original position.",
                          200,
                          2);

        // TODO: Add special ability

        for (int i = 1; i <= 1; i++)
        {
            piece->movePattern.Add(glm::vec2(i,0));
            piece->movePattern.Add(glm::vec2(-i,0));
            piece->movePattern.Add(glm::vec2(0,i));
            piece->movePattern.Add(glm::vec2(0,-i));

            piece->movePattern.Add(glm::vec2(i,i));
            piece->movePattern.Add(glm::vec2(i,-i));
            piece->movePattern.Add(glm::vec2(-i,i));
            piece->movePattern.Add(glm::vec2(-i,-i));
        }

        break;
    case 14:
        piece = new Piece("Cannon",
                          "data/Piece-WhiteCannon.png",
                          "data/Piece-BlackCannon.png",
                          "Can move 1 space in any direction. Can shoot a cannon ball straight forwards. TYhe cannon ball can only hit the 4th and 5th space infront of the cannon. After use, the cannon is removed from the board.",
                          350,
                          1);

        // TODO: Add special ability

        for (int i = 1; i <= 1; i++)
        {
            piece->movePattern.Add(glm::vec2(i,0));
            piece->movePattern.Add(glm::vec2(-i,0));
            piece->movePattern.Add(glm::vec2(0,i));
            piece->movePattern.Add(glm::vec2(0,-i));

            piece->movePattern.Add(glm::vec2(i,i));
            piece->movePattern.Add(glm::vec2(i,-i));
            piece->movePattern.Add(glm::vec2(-i,i));
            piece->movePattern.Add(glm::vec2(-i,-i));
        }

        break;

    default:
        LogError("Failed to create a piece for shop");
    }

    return piece;
}

void Shop::SetShopPiecesToWhite(bool isWhite)
{
    if (items.Empty())
    {
        FillShopItems();
    }

    LinkedList<Piece*>::Iterator piece = items.Begin();

    for (; piece != items.End(); ++piece)
    {
        if (isWhite)
        {
            (*piece)->icon = (*piece)->iconWhite;
        }
        else
        {
            (*piece)->icon = (*piece)->iconBlack;
        }

        (*piece)->isWhite = isWhite;
    }
}

void Shop::FillShopItems()
{
    int y = 430;
    for (int i = 0; i < 10; i++)
    {
        Piece* piece = CreateRandomPiece();

        if (i > 0 && i % 5 == 0)
        {
            y += 30;
        }

        *piece->iconWhite->matrix.x = 140 + ((i % 5) * 50);
        *piece->iconWhite->matrix.y = y;
        *piece->iconBlack->matrix.x = 140 + ((i % 5) * 50);
        *piece->iconBlack->matrix.y = y;

        items.Append(piece);
    }
}

void Shop::Update()
{
    LinkedList<Piece*>::Iterator piece = items.Begin();

    for (; piece != items.End(); ++piece)
    {
        if ((*piece)->icon->IsPressed())
        {
            activePiece = (*piece);
            activePiece->listNode = piece.curNode;
        }

        (*piece)->icon->Update();
    }
}
