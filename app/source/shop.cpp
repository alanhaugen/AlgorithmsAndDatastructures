#include "shop.h"

Shop::Shop()
{
    randomCard = new Sprite("data/Card-Random.png", renderer->windowWidth - 65, 265, 2.0, 2.0, glm::vec2(0.5, 0));
    restockShop = new Sprite("data/B_Restock.png", renderer->windowWidth - 65, 450, 0.5, 0.5, glm::vec2(0.5, 0));

    costTextRandomCard      = new Text("Cost " + String(WildcardCost), 0, 0, 0.8, 0.8, glm::vec2(0.5, 1));
    randomCardText1         = new Text("Draw", 0, 0, 0.8, 0.8, glm::vec2(0.5, 1));
    randomCardText2         = new Text("Random", 0, 0, 0.8, 0.8, glm::vec2(0.5, 1));
    costTextRestockShop     = new Text("Cost " + String(RestockShopCost), 0, 0, 0.8, 0.8, glm::vec2(0.5, 1));
    nameTextRestockShop     = new Text("Restock", 0, 0, 0.8, 0.8, glm::vec2(0.5, 0));
    nameTextRestockShop2    = new Text("Shop", 0, 0, 0.8, 0.8, glm::vec2(0.5, 0));

    isWhitesTurn     = true;

    unshuffledDeckOfCards.Append(CreateKing());
    unshuffledDeckOfCards.Append(CreateKing());

    unshuffledDeckOfCards.Append(CreateMonster());
    unshuffledDeckOfCards.Append(CreateMonster());
    unshuffledDeckOfCards.Append(CreateMonster());

    unshuffledDeckOfCards.Append(CreateQueen());
    unshuffledDeckOfCards.Append(CreateQueen());

    unshuffledDeckOfCards.Append(CreatePrince());
    unshuffledDeckOfCards.Append(CreatePrince());
    unshuffledDeckOfCards.Append(CreatePrince());

    unshuffledDeckOfCards.Append(CreatePrincess());
    unshuffledDeckOfCards.Append(CreatePrincess());
    unshuffledDeckOfCards.Append(CreatePrincess());

    unshuffledDeckOfCards.Append(CreateShieldMan());
    unshuffledDeckOfCards.Append(CreateShieldMan());
    unshuffledDeckOfCards.Append(CreateShieldMan());
    unshuffledDeckOfCards.Append(CreateShieldMan());
    unshuffledDeckOfCards.Append(CreateShieldMan());
    unshuffledDeckOfCards.Append(CreateShieldMan());

    unshuffledDeckOfCards.Append(CreateStallion());
    unshuffledDeckOfCards.Append(CreateStallion());
    unshuffledDeckOfCards.Append(CreateStallion());

    unshuffledDeckOfCards.Append(CreateJester());
    unshuffledDeckOfCards.Append(CreateJester());
    unshuffledDeckOfCards.Append(CreateJester());

    unshuffledDeckOfCards.Append(CreateFence());
    unshuffledDeckOfCards.Append(CreateFence());
    unshuffledDeckOfCards.Append(CreateFence());
    unshuffledDeckOfCards.Append(CreateFence());
    unshuffledDeckOfCards.Append(CreateFence());
    unshuffledDeckOfCards.Append(CreateFence());

    unshuffledDeckOfCards.Append(CreateKnight());
    unshuffledDeckOfCards.Append(CreateKnight());
    unshuffledDeckOfCards.Append(CreateKnight());

    unshuffledDeckOfCards.Append(CreatePeasant());
    unshuffledDeckOfCards.Append(CreatePeasant());
    unshuffledDeckOfCards.Append(CreatePeasant());
    unshuffledDeckOfCards.Append(CreatePeasant());
    unshuffledDeckOfCards.Append(CreatePeasant());
    unshuffledDeckOfCards.Append(CreatePeasant());

    unshuffledDeckOfCards.Append(CreateBishop());
    unshuffledDeckOfCards.Append(CreateBishop());
    unshuffledDeckOfCards.Append(CreateBishop());

    unshuffledDeckOfCards.Append(CreateHydra());
    unshuffledDeckOfCards.Append(CreateHydra());
    unshuffledDeckOfCards.Append(CreateHydra());

    unshuffledDeckOfCards.Append(CreateRogue());
    unshuffledDeckOfCards.Append(CreateRogue());
    unshuffledDeckOfCards.Append(CreateRogue());

    unshuffledDeckOfCards.Append(CreateDeserter());
    unshuffledDeckOfCards.Append(CreateDeserter());
    unshuffledDeckOfCards.Append(CreateDeserter());

    unshuffledDeckOfCards.Append(CreateCannon());
    unshuffledDeckOfCards.Append(CreateCannon());
    unshuffledDeckOfCards.Append(CreateCannon());

    unshuffledDeckOfCards.Append(CreateRook());
    unshuffledDeckOfCards.Append(CreateRook());
    unshuffledDeckOfCards.Append(CreateRook());

    // Populize shop deck
    while (unshuffledDeckOfCards.Empty() == false)
    {
        shopItems.Push(unshuffledDeckOfCards.RemoveAt(random.RandomRange(0, unshuffledDeckOfCards.Size())));
    }

    StockShopFront();
}

Piece* CreateKing()
{
    Piece* piece = new Piece("King",
                             "data/Piece-WhiteKing.png",
                             "data/Piece-BlackKing.png",
                             "Moves like a king in chess. Can move 1 tile in any direction.",
                             130,
                             10,
                             "data/InfoboardWood_King.png",
                             1);

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

    return piece;
}

Piece* CreateQueen()
{
    Piece* piece = new Piece("Queen",
                             "data/Piece-WhiteQueen.png",
                             "data/Piece-BlackQueen.png",
                             "Moves like a queen in chess.",
                             150,
                             5,
                             "data/InfoboardWood_Queen.png",
                             10);

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

    return piece;
}

Piece* CreateMonster()
{
    Piece* piece = new Piece("Monster",
                             "data/Piece-WhiteMonster.png",
                             "data/Piece-BlackMonster.png",
                             "Can move into any adjacent square for 5 tiles.",
                             210,
                             0,
                             "data/InfoboardWood_Monster.png",
                             5);

    for (int y = 1; y <= piece->range; y++)
    {
        for (int x = 1; x <= piece->range; x++)
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

    piece->isPerpendicularOnly = true;

    return piece;
}

Piece* CreatePrince()
{
    Piece* piece = new Piece("Prince",
                             "data/Piece-WhitePrince.png",
                             "data/Piece-BlackPrince.png",
                             "Can move 4 tiles forwards/back/left/right, then attack left/right diagonal. Can jump over fences.",
                             90,
                             4,
                             "data/InfoboardWood_Prince.png",
                             4,
                             "Jumping",
                             true);

    // TODO: Add attack after move phase
    for (int i = 1; i <= 4; i++)
    {
        piece->movePattern.Add(glm::vec2(i,0));
        piece->movePattern.Add(glm::vec2(-i,0));
        piece->movePattern.Add(glm::vec2(0,i));
        piece->movePattern.Add(glm::vec2(0,-i));
    }

    return piece;
}

Piece* CreatePrincess()
{
    Piece* piece = new Piece("Princess",
                             "data/Piece-WhitePrincess.png",
                             "data/Piece-BlackPrincess.png",
                             "Moves like a queen in chess. Can move 3 tiles in any direction. Transformer. Can acquire the qualities of adjacent friendly pieces at will.",
                             160,
                             8,
                             "data/InfoboardWood_Princess.png",
                             3,
                             "Jumping",
                             true);

    // TODO: Add special ability
    for (int i = 1; i <= 3; i++)
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

    return piece;

}

Piece* CreateShieldMan()
{
    Piece* piece = new Piece("Shield Man",
                             "data/Piece-WhiteShield.png",
                             "data/Piece-BlackShield.png",
                             "Can move 1 tile forward or 1 tile sideways. This piece cannot capture other pieces. The tiles in front will become heavy.",
                             70,
                             1,
                             "data/InfoboardWood_ShieldMan.png",
                             1);

    // TODO: Special weight quality and capture quality
    piece->canCapture = false;

    piece->movePattern.Add(glm::vec2(0, 1));
    piece->movePattern.Add(glm::vec2(1, 0));
    piece->movePattern.Add(glm::vec2(-1, 0));
    piece->movePattern.Add(glm::vec2(0, -1));

    piece->weightPattern.Add(glm::vec2(1,0));
    piece->weightPattern.Add(glm::vec2(-1,0));
    piece->weightPattern.Add(glm::vec2(1,1));
    piece->weightPattern.Add(glm::vec2(0,1));
    piece->weightPattern.Add(glm::vec2(-1,1));

    return piece;
}

Piece* CreateStallion()
{
    Piece* piece = new Piece("Stallion",
                             "data/Piece-WhiteStallion.png",
                             "data/Piece-BlackStallion.png",
                             "Moves like a knight in chess. Either two steps forward and one to the side, or one step forward and two to the side. Can jump over fences.",
                             60,
                             1,
                             "data/InfoboardWood_Stallion.png",
                             3,
                             "Jumping",
                             true);

    piece->movePattern.Add(glm::vec2(1,2));
    piece->movePattern.Add(glm::vec2(1,-2));
    piece->movePattern.Add(glm::vec2(-1,-2));
    piece->movePattern.Add(glm::vec2(-1,2));
    piece->movePattern.Add(glm::vec2(2,1));
    piece->movePattern.Add(glm::vec2(2,-1));
    piece->movePattern.Add(glm::vec2(-2,1));
    piece->movePattern.Add(glm::vec2(-2,-1));

    return piece;
}

Piece* CreateJester()
{
    Piece* piece = new Piece("Jester",
                             "data/Piece-WhiteJester.png",
                             "data/Piece-BlackJester.png",
                             "Moves diagonally 2 spaces in any direction.",
                             110,
                             3,
                             "data/InfoboardWood_Jester.png",
                             10,
                             "Jumping",
                             false);

    for (int i = 1; i <= 5; i++)
    {
        piece->movePattern.Add(glm::vec2((i*2)+1, (i*2)+1));
        piece->movePattern.Add(glm::vec2((i*2)+1, (-i*2)-1));
        piece->movePattern.Add(glm::vec2((-i*2)-1, (i*2)+1));
        piece->movePattern.Add(glm::vec2((-i*2)-1, (-i*2)-1));
        piece->movePattern.Add(glm::vec2((i*2)-1, 0));
        piece->movePattern.Add(glm::vec2(0, (-i*2)-1));
        piece->movePattern.Add(glm::vec2((-i*2)-1, 0));
        piece->movePattern.Add(glm::vec2(0, (i*2)-1));
    }

    piece->movePattern.Add(glm::vec2(1, 1));
    piece->movePattern.Add(glm::vec2(1, 0));
    piece->movePattern.Add(glm::vec2(0, 1));
    piece->movePattern.Add(glm::vec2(0, -1));
    piece->movePattern.Add(glm::vec2(-1, -1));
    piece->movePattern.Add(glm::vec2(-1, 0));
    piece->movePattern.Add(glm::vec2(-1, 1));
    piece->movePattern.Add(glm::vec2(1, -1));

    piece->isJester = true;

    return piece;

}

Piece* CreateFence()
{
    Piece* piece = new Piece("Fence",
                             "data/Piece-WhiteFence.png",
                             "data/Piece-BlackFence.png",
                             "Can be placed on the edge of tiles, is 3 spaces long. Blocks non-jumping pieces from passing. Can only be placed horizontally.",
                             10,
                             0,
                             "data/InfoboardWood_Fence.png",
                             0,
                             "Blocking");

    piece->invinsible = true;

    return piece;
}

Piece* CreateKnight()
{
    Piece* piece = new Piece("Knight",
                             "data/Piece-WhiteKnight.png",
                             "data/Piece-BlackKnight.png",
                             "Moves like a rook, but only 4 tiles. Can attack diagonally forward left/right if oponent",
                             80,
                             2,
                             "data/InfoboardWood_Knight.png",
                             3,
                             "Grounded");

    for (int i = 1; i <= 2; i++)
    {
        piece->movePattern.Add(glm::vec2(i,0));
        piece->movePattern.Add(glm::vec2(-i,0));
        piece->movePattern.Add(glm::vec2(0,i));
        piece->movePattern.Add(glm::vec2(0,-i));

    }

    piece->captureOnlyMovePattern.Add(Capture(glm::vec2(3, 1), glm::vec2(2, 0)));
    piece->captureOnlyMovePattern.Add(Capture(glm::vec2(3, -1), glm::vec2(2, 0)));

    piece->captureOnlyMovePattern.Add(Capture(glm::vec2(-3, 1), glm::vec2(-2, 0)));
    piece->captureOnlyMovePattern.Add(Capture(glm::vec2(-3, -1), glm::vec2(-2, 0)));

    piece->captureOnlyMovePattern.Add(Capture(glm::vec2(1, 3), glm::vec2(0, 2)));
    piece->captureOnlyMovePattern.Add(Capture(glm::vec2(-1, 3), glm::vec2(0, 2)));

    piece->captureOnlyMovePattern.Add(Capture(glm::vec2(1, -3), glm::vec2(0, -2)));
    piece->captureOnlyMovePattern.Add(Capture(glm::vec2(-1, -3), glm::vec2(0, -2)));

    return piece;
}

Piece* CreatePeasant()
{
    Piece* piece = new Piece("Peasant",
                             "data/Piece-WhitePeasant.png",
                             "data/Piece-BlackPeasant.png",
                             "Only move forward by 1 space, can capture if there is an opponent piece on that space.",
                             30,
                             0,
                             "data/InfoboardWood_Peasant.png",
                             1,
                             "Grounded");

    // Transform into Queen when reaching the other side of the board
    piece->transformedPiece = CreateQueen();

    piece->movePattern.Add(glm::vec2(0,1));
    piece->movePattern.Add(glm::vec2(1,1));
    piece->movePattern.Add(glm::vec2(-1,1));

    return piece;
}

Piece* CreateBishop()
{
    Piece* piece = new Piece("Bishop",
                             "data/Piece-WhiteBishop.png",
                             "data/Piece-BlackBishop.png",
                             "Moves like a bishop. Can move unlimited amount of spaces diagonally in any direction.",
                             80,
                             4,
                             "data/InfoboardWood_Bishop.png",
                             10,
                             "Grounded");

    for (int i = 1; i <= 10; i++)
    {
        piece->movePattern.Add(glm::vec2(i,i));
        piece->movePattern.Add(glm::vec2(-i,-i));
        piece->movePattern.Add(glm::vec2(i,-i));
        piece->movePattern.Add(glm::vec2(-i,i));
    }

    return piece;
}

Piece* CreateHydra()
{
    Piece* piece = new Piece("Hydra",
                             "data/Piece-WhiteHydra.png",
                             "data/Piece-BlackHydra.png",
                             "Can only move 1 space at the time. Can attack up to 3 adjacent enemies.",
                             40,
                             1,
                             "data/InfoboardWood_Hydra.png",
                             1,
                             "Grounded",
                             false,
                             false,
                             true);

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

    // If hydra attacks into a tile, then attack adjacent tiles left/right.

    return piece;
}

Piece* CreateRogue()
{
    Piece* piece = new Piece("Rogue",
                             "data/Piece-WhiteRogue.png",
                             "data/Piece-BlackRogue.png",
                             "Can move 2 tiles in any direction. If the rogue eliminates an enemy piece, the rogue moves back to its original position.",
                             100,
                             2,
                             "data/InfoboardWood_Rogue.png",
                             2,
                             "Ranged",
                             false,
                             true);

    // TODO: Add special ability
    for (int i = 1; i <= 2; i++)
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

    // If Rogues attacks into a tile, then move back to initial tile.

    return piece;
}

Piece* CreateDeserter()
{
    Piece* piece = new Piece("Deserter",
                             "data/Piece-WhiteDeserter.png",
                             "data/Piece-BlackDeserter.png",
                             "Haunts the piece with the highest nobility. Moves up to 4 adjacent tiles.",
                             90,
                             0,
                             "data/InfoboardWood_Deserter.png",
                             4,
                             "Grounded");

    for (int y = 1; y <= piece->range; y++)
    {
        for (int x = 1; x <= piece->range; x++)
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

    piece->isDiagonalOnly = true;

    return piece;
}

Piece* CreateCannon()
{
    Piece* piece = new Piece("Cannon",
                             "data/Piece-WhiteCannon.png",
                             "data/Piece-BlackCannon.png",
                             "Can move 1 space in any direction. Can shoot a cannon ball straight forwards. The cannon ball can only hit the 4th and 5th space infront of the cannon. After use, the cannon is removed from the board.",
                             150,
                             1,
                             "data/InfoboardWood_Cannon.png",
                             1,
                             "Ranged",
                             true,
                             true);

    piece->animatedForm = new Sprite("data/Sprite-CannonballWHITE.png", 0, 0, 0.4, 0.4);

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

    // Cannon can shoot pieces 3 tiles in front of it

    for (int i = 3; i < 10; ++i)
    {
        piece->captureOnlyMovePattern.Add(Capture(glm::vec2(0,i), glm::vec2()));
        piece->captureOnlyMovePattern.Add(Capture(glm::vec2(i,0), glm::vec2()));
        piece->captureOnlyMovePattern.Add(Capture(glm::vec2(-i,0), glm::vec2()));
    }

    piece->canCapture = false;

    return piece;
}


Piece *CreateRook()
{
    Piece* piece = new Piece("Rook",
                             "data/Piece-WhiteRook.png",
                             "data/Piece-BlackRook.png",
                             "Moves perpendicularly",
                             100,
                             3,
                             "data/InfoboardWood_Cannon.png",
                             10,
                             "Grounded");

    for (int i = 1; i <= 10; i++)
    {
        piece->movePattern.Add(glm::vec2(i,0));
        piece->movePattern.Add(glm::vec2(-i,0));
        piece->movePattern.Add(glm::vec2(0,-i));
        piece->movePattern.Add(glm::vec2(0,i));
    }

    return piece;
}

Piece* CreateRock()
{
    Piece* piece = new Piece("Rook",
                             "data/Piece-ObstacleROCK.png",
                             "data/Piece-ObstacleROCK.png",
                             "Obstacle",
                             0,
                             0,
                             "data/InfoboardWood_Cannon.png",
                             0,
                             "Grounded");
}

Piece* CreateTree()
{
    Piece* piece = new Piece("Rook",
                             "data/Piece-ObstacleTREE.png",
                             "data/Piece-ObstacleTREE.png",
                             "Obstacle",
                             0,
                             0,
                             "data/InfoboardWood_Cannon.png",
                             0,
                             "Grounded");
}

Piece* CreateWater()
{
    Piece* piece = new Piece("Rook",
                             "data/Piece-ObstacleWATER.png",
                             "data/Piece-ObstacleWATER.png",
                             "Obstacle",
                             0,
                             0,
                             "data/InfoboardWood_Cannon.png",
                             0,
                             "Grounded");
}

Piece* CreateRiver()
{
    Piece* piece = new Piece("Rook",
                             "data/Piece-ObstacleRIVERHORIZ.png",
                             "data/Piece-ObstacleRIVERHORIZ.png",
                             "Obstacle",
                             0,
                             0,
                             "data/InfoboardWood_Cannon.png",
                             0,
                             "Grounded");
}

Piece* Shop::CreateRandomPiece()
{
    int randomNumber = random.RandomRange(0, PIECE_TYPES_QUANTITY);

    Piece* piece = nullptr;

    switch(randomNumber)
    {
    case 0:
        piece = CreateKing();
        break;

    case 1:
        piece = CreatePrince();
        break;

    case 2:
        piece = CreatePrincess();
        break;

    case 3:
        piece = CreateShieldMan();
        break;

    case 4:
        piece = CreateQueen();
        break;

    case 5:
        piece = CreateMonster();
        break;

    case 6:
        piece = CreatePeasant();
        break;

    case 7:
        piece = CreateKnight();
        break;

    case 8:
        piece = CreateBishop();
        break;

    case 9:
        piece = CreateStallion();
        break;

    case 10:
        piece = CreateJester();
        break;

    case 11:
        piece = CreateFence();
        break;

    case 12:
        piece = CreateHydra();
        break;

    case 13:
        piece = CreateRogue();
        break;

    case 14:
        piece = CreateCannon();
        break;

    case 15:
        piece = CreateDeserter();
        break;

    case 16:
        piece = CreateRook();
        break;

    default:
        LogError("Failed to create a piece for shop");
    }

    return piece;
}

void Shop::SetShopPiecesToWhite(bool isWhite)
{
    isWhitesTurn = isWhite;

    Update();

    LinkedList<Piece*>::Iterator piece = itemsStoreFront.Begin();

    if (itemsStoreFront.Empty() == true)
    {
        return;
    }

    for (; piece != NULL; ++piece)
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

void Shop::StockShopFront()
{
    int y = 80 * 1.75;

    itemsStoreFront.Clear();

    for (int i = 0; i < 10; i++)
    {
        if (shopItems.Empty() == true)
        {
            return;
        }

        Piece* piece = shopItems.Pop();

        if (i > 0 && i % 5 == 0)
        {
            y += 90 * 3.00;
        }

        *piece->iconWhite->matrix.x = (290 + ((i % 5) * 100))*1.60;
        *piece->iconWhite->matrix.y = y;
        *piece->iconBlack->matrix.x = (290 + ((i % 5) * 100))*1.60;
        *piece->iconBlack->matrix.y = y;

        itemsStoreFront.Append(piece);
    }

    SetShopPiecesToWhite(isWhitesTurn);
}

void Shop::Update()
{
    activePiece = nullptr;

    restockShop->Update();

    if (itemsStoreFront.Empty() && shopItems.Empty() == false)
    {
        StockShopFront();
    }

    if (itemsStoreFront.Empty())
    {
        activePiece = nullptr;
        return;
    }

    LinkedList<Piece*>::Iterator piece = itemsStoreFront.Begin();

    for (; piece != NULL; ++piece)
    {
        if ((*piece)->backgroundCard->IsPressed() && !PopUpOpen)
        {
            activePiece = (*piece);
            activePiece->listNode = piece.curNode;
        }

        (*piece)->Update();

        if ((*piece)->backgroundCard->IsHoveredOver() && !PopUpOpen)
        {
            *(*piece)->buyText->matrix.x = *(*piece)->icon->matrix.x - 10*1.55;
            *(*piece)->buyText->matrix.y = *(*piece)->icon->matrix.y - 20*1.55;
            (*piece)->buyText->Update();
        }

        *(*piece)->nameText->matrix.x = *(*piece)->icon->matrix.x;
        *(*piece)->nameText->matrix.y = *(*piece)->icon->matrix.y + 30*1.75;
        (*piece)->nameText->Update();

        *(*piece)->movementTypeText->matrix.x = *(*piece)->icon->matrix.x - 5;
        *(*piece)->movementTypeText->matrix.y = *(*piece)->icon->matrix.y + 40*1.75;
        (*piece)->movementTypeText->Update();

        *(*piece)->movementText->matrix.x = *(*piece)->icon->matrix.x - 5;
        *(*piece)->movementText->matrix.y = *(*piece)->icon->matrix.y + 50*1.75;
        (*piece)->movementText->Update();

        /**(*piece)->descriptionText->matrix.x = *(*piece)->icon->matrix.x - 10*1.75;
        *(*piece)->descriptionText->matrix.y = *(*piece)->icon->matrix.y + 30*1.75;
        (*piece)->descriptionText->Update();*/

        *(*piece)->nobilityText->matrix.x = *(*piece)->icon->matrix.x - 5;
        *(*piece)->nobilityText->matrix.y = *(*piece)->icon->matrix.y + 60*1.75;
        (*piece)->nobilityText->Update();

        *(*piece)->costText->matrix.x = *(*piece)->icon->matrix.x - 5;
        *(*piece)->costText->matrix.y = *(*piece)->icon->matrix.y + 70*1.75;
        (*piece)->costText->Update();

        *(*piece)->backgroundCard->matrix.x = *(*piece)->icon->matrix.x - 10*1.75;
        *(*piece)->backgroundCard->matrix.y = *(*piece)->icon->matrix.y - 10*1.75;
        (*piece)->backgroundCard->Update();
    }

    if (shopItems.Empty() == false)
    {
        randomCard->Update();
    }

    if (randomCard->IsHoveredOver() && shopItems.Empty() == false && !PopUpOpen)
    {
        *costTextRandomCard->matrix.x = *randomCard->matrix.x;
        *costTextRandomCard->matrix.y = *randomCard->matrix.y + 135;
        *randomCardText1->matrix.x = *randomCard->matrix.x;
        *randomCardText1->matrix.y = *randomCard->matrix.y - 5;
        *randomCardText2->matrix.x = *randomCard->matrix.x;
        *randomCardText2->matrix.y = *randomCard->matrix.y - 25;
        costTextRandomCard->Update();
        randomCardText1->Update();
        randomCardText2->Update();
    }
    if (randomCard->IsPressed() && shopItems.Empty() == false && !PopUpOpen)
    {
        activePiece = shopItems.Pop();
        activePiece->listNode = nullptr;
        activePiece->price = WildcardCost;

        if (isWhitesTurn == false)
        {
            activePiece->icon = activePiece->iconBlack;
            activePiece->isWhite = false;
        }
    }
    if (restockShop->IsHoveredOver() && shopItems.Empty() == false && !PopUpOpen)
    {
        *costTextRestockShop->matrix.x = *restockShop->matrix.x;
        *costTextRestockShop->matrix.y = *restockShop->matrix.y + 90;
        *nameTextRestockShop->matrix.x = *restockShop->matrix.x;
        *nameTextRestockShop->matrix.y = *restockShop->matrix.y -50;
        *nameTextRestockShop2->matrix.x = *restockShop->matrix.x;
        *nameTextRestockShop2->matrix.y = *restockShop->matrix.y - 25;

        costTextRestockShop->Update();
        nameTextRestockShop->Update();
        nameTextRestockShop2->Update();
    }
}
