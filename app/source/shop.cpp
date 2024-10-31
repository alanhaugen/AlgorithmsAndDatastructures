#include "shop.h"

Shop::Shop()
{
    background = new Sprite("data/ShopBackgroundImage.png", 0, 0, 0.75, 0.75);
    randomCard = new Sprite("data/Card-Random.png", 600, 300, 2.0, 2.0);
    costTextRandomCard = new Text("Cost " + String(WildcardCost), 0,0, 0.4, 0.4);

    numberOfFences = 0;
    numberOfKings = 0;
    numberOfQueens = 0;
    numberOfMonsters = 0;
    isWhitesTurn = true;

    //2 Kings
    unshuffledDeckOfCards.Append(CreateKing());
    unshuffledDeckOfCards.Append(CreateKing());
    //2 Queens
    unshuffledDeckOfCards.Append(CreateQueen());
    unshuffledDeckOfCards.Append(CreateQueen());
    //3 Princes
    unshuffledDeckOfCards.Append(CreatePrince());
    unshuffledDeckOfCards.Append(CreatePrince());
    unshuffledDeckOfCards.Append(CreatePrince());
    //3 Princessses
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

    // Populize shop deck
    while (unshuffledDeckOfCards.Empty() == false)
    {
        shopItems.Push(unshuffledDeckOfCards.RemoveAt(random.RandomRange(0, unshuffledDeckOfCards.Size())));
    }

    StockShopFront();
}

Piece* Shop::CreateKing()
{
    Piece* piece = new Piece("King",
              "data/Piece-WhiteKing.png",
              "data/Piece-BlackKing.png",
              "Moves like a king in chess. Can move 1 tile in any direction.",
              200,
              10,
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

Piece* Shop::CreateQueen()
{
    Piece* piece = new Piece("Queen",
                     "data/Piece-WhiteQueen.png",
                     "data/Piece-BlackQueen.png",
                     "Moves like a queen in chess.",
                     150,
                     5,
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

Piece* Shop::CreatePrince()
{
    Piece* piece = new Piece("Prince",
                     "data/Piece-WhitePrince.png",
                     "data/Piece-BlackPrince.png",
                     "Can move 4 tiles forwards/back/left/right, then attack left/right diagonal. Can jump over fences.",
                     90,
                     6,
                     4);

    piece->isJumping = true;

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

Piece* Shop::CreatePrincess()
{
    Piece* piece = new Piece("Princess",
                     "data/Piece-WhitePrincess.png",
                     "data/Piece-BlackPrincess.png",
                     "Moves like a queen in chess. Can move 3 tiles in any direction. Transformer. Can acquire the qualities of adjacent friendly pieces at will.",
                     120,
                     8,
                     3);

    piece->isJumping = true;
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

Piece* Shop::CreateShieldMan()
{
    Piece* piece = new Piece("Shield Man",
                     "data/Piece-WhiteShield.png",
                     "data/Piece-BlackShield.png",
                     "Can move 1 tile forward or 1 tile sideways. This piece cannot capture other pieces. The tiles in front will become heavy.",
                     50,
                     1,
                     1);

    // TODO: Special weight quality and capture quality
    piece->canCapture = false;

    piece->movePattern.Add(glm::vec2(0, 1));
    piece->movePattern.Add(glm::vec2(1, 0));
    piece->movePattern.Add(glm::vec2(-1, 0));

    piece->weightPattern.Add(glm::vec2(1,0));
    piece->weightPattern.Add(glm::vec2(-1,1));
    piece->weightPattern.Add(glm::vec2(1,1));
    piece->weightPattern.Add(glm::vec2(0,1));
    piece->weightPattern.Add(glm::vec2(-1,1));

    return piece;
}

Piece* Shop::CreateStallion()
{
    Piece* piece = new Piece("Stallion",
                     "data/Piece-WhiteStallion.png",
                     "data/Piece-BlackStallion.png",
                     "Moves like a knight in chess. Either two steps forward and one to the side, or one step forward and two to the side. Can jump over fences.",
                     60,
                     1,
                     3);

    piece->isJumping = true;
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

Piece* Shop::CreateJester()
{
    Piece* piece = new Piece("Jester",
                     "data/Piece-WhiteJester.png",
                     "data/Piece-BlackJester.png",
                     "Moves diagonally 2 spaces in any direction.",
                     75,
                     3,
                     2);

    piece->isJumping = true;

    for (int i = 1; i <= 2; i++)
    {
        piece->movePattern.Add(glm::vec2(i,i));
        piece->movePattern.Add(glm::vec2(i,-i));
        piece->movePattern.Add(glm::vec2(-i,i));
        piece->movePattern.Add(glm::vec2(-i,-i));
    }

    return piece;

}

Piece* Shop::CreateFence()
{
    Piece* piece = new Piece("Fence",
                     "data/Piece-WhiteFence.png",
                     "data/Piece-BlackFence.png",
                     "Can be placed on the edge of tiles, is 3 spaces long. Blocks non-jumping pieces from passing. Can only be placed horizontally.",
                     40,
                     0,
                     0);

    piece->invinsible = true;

    return piece;
}

Piece* Shop::CreateKnight()
{
    Piece* piece = new Piece("Knight",
                     "data/Piece-WhiteKnight.png",
                     "data/Piece-BlackKnight.png",
                     "Moves like a rook, but only 5 tiles forwards (or backwards or ot the side)",
                     50,
                     2,
                     5);

    for (int i = 1; i <= 4; i++)
    {
        piece->movePattern.Add(glm::vec2(i,0));
        piece->movePattern.Add(glm::vec2(-i,0));
        piece->movePattern.Add(glm::vec2(0,i));
        piece->movePattern.Add(glm::vec2(0,-i));

    }

    piece->captureOnlyMovePattern.Add(glm::vec2(4+1,0+1));
    piece->captureOnlyMovePattern.Add(glm::vec2(4+1,0-1));

    piece->captureOnlyMovePattern.Add(glm::vec2(-4-1,0+1));
    piece->captureOnlyMovePattern.Add(glm::vec2(-4-1,0-1));

    piece->captureOnlyMovePattern.Add(glm::vec2(0+1,4+1));
    piece->captureOnlyMovePattern.Add(glm::vec2(0-1,4+1));

    piece->captureOnlyMovePattern.Add(glm::vec2(0+1,-4-1));
    piece->captureOnlyMovePattern.Add(glm::vec2(0-1,-4-1));

    return piece;
}

Piece* Shop::CreatePeasant()
{
    Piece* piece = new Piece("Peasant",
                     "data/Piece-WhitePeasant.png",
                     "data/Piece-BlackPeasant.png",
                     "Only move forward by 1 space, can capture if there is an opponent piece on that space.",
                     20,
                     0,
                     1);

    // TODO: Add promotion when reaching other side of board
    piece->movePattern.Add(glm::vec2(0,1));

    return piece;
}

Piece* Shop::CreateBishop()
{
    Piece* piece = new Piece("Bishop",
                     "data/Piece-WhiteBishop.png",
                     "data/Piece-BlackBishop.png",
                     "Moves like a bishop. Can move unlimited amount of spaces diagonally in any direction.",
                     80,
                     4,
                     10);

    for (int i = 1; i <= 10; i++)
    {
        piece->movePattern.Add(glm::vec2(i,i));
        piece->movePattern.Add(glm::vec2(i,-i));
        piece->movePattern.Add(glm::vec2(-i,i));
        piece->movePattern.Add(glm::vec2(-i,-i));
    }

    return piece;
}

Piece* Shop::CreateHydra()
{
    Piece* piece = new Piece("Hydra",
                     "data/Piece-WhiteHydra.png",
                     "data/Piece-BlackHydra.png",
                     "Can only move 1 space at the time. Can attack up to 3 adjacent enemies.",
                     180,
                     1,
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

    return piece;
}

Piece* Shop::CreateRogue()
{
    Piece* piece = new Piece("Rogue",
                     "data/Piece-WhiteRogue.png",
                     "data/Piece-BlackRogue.png",
                     "Can move 2 tiles in any direction. If the rogue eliminates an enemy piece, the rogue moves back to its original position.",
                     200,
                     2,
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

    return piece;
}

Piece* Shop::CreateDeserter()
{
    Piece* piece = new Piece("Deserter",
                     "data/Piece-WhiteDeserter.png",
                     "data/Piece-BlackDeserter.png",
                     "Haunts the piece with the highest nobility. Moves up to 4 adjacent tiles.",
                     50,
                     0,
                     4);

    for (int i = 1; i <= 4; i++)
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

Piece* Shop::CreateCannon()
{
    Piece* piece = new Piece("Cannon",
                     "data/Piece-WhiteCannon.png",
                     "data/Piece-BlackCannon.png",
                     "Can move 1 space in any direction. Can shoot a cannon ball straight forwards. The cannon ball can only hit the 4th and 5th space infront of the cannon. After use, the cannon is removed from the board.",
                     350,
                     1,
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

    return piece;
}



Piece* Shop::CreateRandomPiece()
{
    int randomNumber = random.RandomRange(0, PIECE_TYPES_QUANTITY);

    Piece* piece = nullptr;

    switch(randomNumber)
    {
    case 0:

        if (numberOfKings >= MAX_NUMBER_OF_KINGS)
        {
            return CreateRandomPiece();
        }

        numberOfKings++;

        piece = CreateKing();

        break;
    case 1:
        piece = new Piece("Prince",
                         "data/Piece-WhitePrince.png",
                         "data/Piece-BlackPrince.png",
                         "Can move 4 tiles forwards/back/left/right, then attack left/right diagonal. Can jump over fences.",
                         90,
                         6);



        break;
    case 2:
        piece = new Piece("Princess",
                         "data/Piece-WhitePrincess.png",
                         "data/Piece-BlackPrincess.png",
                         "Moves like a queen in chess. Can move 3 tiles in any direction. Transformer. Can acquire the qualities of adjacent friendly pieces at will.",
                         120,
                         8);



        break;
    case 3:
        piece = new Piece("Shield Man",
                         "data/Piece-WhiteShield.png",
                         "data/Piece-BlackShield.png",
                         "Can move 1 tile forward or 1 tile sideways. This piece cannot capture other pieces. The tiles in front will become heavy.",
                         50,
                         1);

        // TODO: Special weight quality and capture quality
        piece->movePattern.Add(glm::vec2(0, 1));
        piece->movePattern.Add(glm::vec2(1, 0));
        piece->movePattern.Add(glm::vec2(-1, 0));

        break;
    case 4:

        if (numberOfQueens >= MAX_NUMBER_OF_QUEENS)
        {
            return CreateRandomPiece();
        }

        numberOfQueens++;

        piece = new Piece("Queen",
                         "data/Piece-WhiteQueen.png",
                         "data/Piece-BlackQueen.png",
                         "Moves like a queen in chess.",
                         150,
                         5);



        break;
    case 5:

        if (numberOfMonsters >= MAX_NUMBER_OF_MONSTERS)
        {
            return CreateRandomPiece();
        }

        numberOfMonsters++;

        piece = new Piece("Monster",
                         "data/Piece-WhiteMonster.png",
                         "data/Piece-BlackMonster.png",
                         "Can move into any adjacent square for 5 tiles.",
                         150,
                         0);

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



        break;
    case 7:
        piece = new Piece("Knight",
                         "data/Piece-WhiteRook.png",
                         "data/Piece-BlackRook.png",
                          "Moves like a rook, but only 5 tiles forwards (or backwards or ot the side)",
                          50,
                          2);



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

        break;
    case 10:
        piece = new Piece("Jester",
                          "data/Piece-WhiteJester.png",
                          "data/Piece-BlackJester.png",
                          "Moves diagonally 2 spaces in any direction.",
                          75,
                          3);



        break;
    case 11:
        if (numberOfFences >= MAX_NUMBER_OF_FENCES)
        {
            return CreateRandomPiece();
        }

        numberOfFences++;

        piece = new Piece("Fence",
                          "data/Piece-WhiteFence.png",
                          "data/Piece-BlackFence.png",
                          "Can be placed on the edge of tiles, is 3 spaces long. Blocks non-jumping pieces from passing. Can only be placed horizontally.",
                          40,
                          0);



        break;
    case 12:
        piece = new Piece("Hydra",
                          "data/Piece-WhiteHydra.png",
                          "data/Piece-BlackHydra.png",
                          "Can only move 1 space at the time. Can attack up to 3 adjacent enemies.",
                          180,
                          1);



        break;
    case 13:
        piece = new Piece("Rogue",
                          "data/Piece-WhiteRogue.png",
                          "data/Piece-BlackRogue.png",
                          "Can move 2 tiles in any direction. If the rogue eliminates an enemy piece, the rogue moves back to its original position.",
                          200,
                          2);

        break;
    case 14:
        piece = new Piece("Cannon",
                          "data/Piece-WhiteCannon.png",
                          "data/Piece-BlackCannon.png",
                          "Can move 1 space in any direction. Can shoot a cannon ball straight forwards. The cannon ball can only hit the 4th and 5th space infront of the cannon. After use, the cannon is removed from the board.",
                          350,
                          1);



        break;
    case 15:
        piece = new Piece("Deserter",
                          "data/Piece-WhiteDeserter.png",
                          "data/Piece-BlackDeserter.png",
                          "Haunts the piece with the highest nobility. Moves up to 4 adjacent tiles.",
                          50,
                          0);



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
    int y = 150 * 1.75;

    for (int i = 0; i < 10; i++)
    {
        if (shopItems.Empty() == true)
        {
            return;
        }

        Piece* piece = shopItems.Pop();

        if (i > 0 && i % 5 == 0)
        {
            y += 90 * 1.75;
        }

        *piece->iconWhite->matrix.x = (100 + ((i % 5) * 50))*1.75;
        *piece->iconWhite->matrix.y = y;
        *piece->iconBlack->matrix.x = (100 + ((i % 5) * 50))*1.75;
        *piece->iconBlack->matrix.y = y;

        itemsStoreFront.Append(piece);
    }
}

void Shop::Update()
{
    background->Update();
    activePiece = nullptr;

    if (itemsStoreFront.Empty())
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
        if ((*piece)->icon->IsPressed())
        {
            activePiece = (*piece);
            activePiece->listNode = piece.curNode;
        }

        (*piece)->Update();

        if ((*piece)->icon->IsHoveredOver())
        {
            *(*piece)->nameText->matrix.x = *(*piece)->icon->matrix.x - 10*1.75;
            *(*piece)->nameText->matrix.y = *(*piece)->icon->matrix.y - 60*1.75;
            (*piece)->nameText->Update();

            *(*piece)->movementTypeText->matrix.x = *(*piece)->icon->matrix.x - 10*1.75;
            *(*piece)->movementTypeText->matrix.y = *(*piece)->icon->matrix.y - 50*1.75;
            (*piece)->movementTypeText->Update();

            *(*piece)->movementText->matrix.x = *(*piece)->icon->matrix.x - 10*1.75;
            *(*piece)->movementText->matrix.y = *(*piece)->icon->matrix.y - 40*1.75;
            (*piece)->movementText->Update();

            *(*piece)->descriptionText->matrix.x = *(*piece)->icon->matrix.x - 10*1.75;
            *(*piece)->descriptionText->matrix.y = *(*piece)->icon->matrix.y - 30*1.75;
            (*piece)->descriptionText->Update();

            *(*piece)->nobilityText->matrix.x = *(*piece)->icon->matrix.x - 10*1.75;
            *(*piece)->nobilityText->matrix.y = *(*piece)->icon->matrix.y - 20*1.75;
            (*piece)->nobilityText->Update();

            *(*piece)->costText->matrix.x = *(*piece)->icon->matrix.x - 10*1.75;
            *(*piece)->costText->matrix.y = *(*piece)->icon->matrix.y - 10*1.75;
            (*piece)->costText->Update();
        }
    }

    if (shopItems.Empty() == false)
    {
        randomCard->Update();
    }

    if (randomCard->IsHoveredOver() && shopItems.Empty() == false)
    {
        *costTextRandomCard->matrix.x = *randomCard->matrix.x + 30;
        *costTextRandomCard->matrix.y = *randomCard->matrix.y - 10*1.75;
        costTextRandomCard->Update();
    }
    if (randomCard->IsPressed() && shopItems.Empty() == false)
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
}
