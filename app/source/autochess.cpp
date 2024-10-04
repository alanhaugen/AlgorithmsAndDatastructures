#include "autochess.h"

Autochess::Autochess()
{
}

void Autochess::Init()
{
    gameBoard = new Board();
    shop = new Shop();
    players = Array<Player>(2);
    /*players[0].pieces.Append(Piece("Rook",
                                   "data/Piece-WhiteRook.png",
                                   "Rook like in chess",
                                   1,
                                   0));*/
    king = new Piece("king",
                     "data/Piece-WhiteRook.png",
                     "Moves like a king in chess. Can move 1 tile in any direction.",
                     200,
                     10);
    prince = new Piece("Prince",
                       "data/Piece-WhiteRook.png",
                       "Can move 4 tiles forwards/back/left/right, then attack left/right diagonal. Can jump over fences.",
                       90,
                       6);
    princess = new Piece("Princess",
                         "data/Piece-WhiteRook.png",
                         "Moves like a queen in chess. Can move 3 tiles in any direction. Transformer. Can acquire the qualities of adjacent friendly pieces at will.",
                         120,
                         8);
    shield = new Piece("Shield Man",
                       "data/Piece-WhiteRook.png",
                       "Can move 1 tile forward or 1 tile sideways. This piece cannot capture other pieces. The tile in front will become heavy.",
                       50,
                       1);
    queen = new Piece("Queen",
                      "data/Piece-WhiteRook.png",
                      "Moves like a queen in chess.",
                      150,
                      5);
    monster = new Piece("Monster",
                        "data/Piece-WhiteRook.png",
                        "Can move into any adjacent square for 5 tiles.",
                        150,
                        0);
    peasant = new Piece("Peasant",
                        "data/Piece-WhiteRook.png",
                        "Only move forward by 1 space, can capture if there is an opponent piece on that space.",
                        20,
                        0);
    knight = new Piece("Knight",
                       "data/Piece-WhiteRook.png",
                       "Moves like a rook, but only 5 tiles forwards (or backwards or ot the side)",
                       50,
                       2);
    bishop = new Piece("Bishop",
                       "data/Piece-WhiteRook.png",
                       "Moves like a bishop. Can move unlimited amount of spaces diagonally in any direction.",
                       80,
                       4);
    stallion = new Piece("Stallion",
                         "data/Piece-WhiteRook.png",
                         "Moves like a knight in chess. Either two steps forward and one to the side, or one step forward and two to the side. Can jump over fences.",
                         60,
                         1);
    jester = new Piece("Jester",
                       "data/Piece-WhiteRook.png",
                       "Moves diagonally 2 spaces in any direction.",
                       75,
                       3);
    fence = new Piece("Fence",
                      "data/Piece-WhiteRook.png",
                      "Can be placed on the edge of tiles, is 3 spaces long. Blocks non-jumping pieces from passing. CAn only be placed horizontally.",
                      40,
                      0);
    hydra = new Piece("Hydra",
                      "data/Piece-WhiteRook.png",
                      "Can only move 1 space at the time. Can attack up to 3 adjacent enemies.",
                      180,
                      1);
    rogue = new Piece("Rogue",
                      "data/Piece-WhiteRook.png",
                      "Can move 2 tiles in any direction. If the rogue eliminates an enemy piece, the rogue moves back to its original position.",
                      200,
                      2);
    cannon = new Piece("Cannon",
                       "data/Piece-WhiteRook.png",
                       "Can move 1 space in any direction. Can shoot a cannon ball straight forwards. TYhe cannon ball can only hit the 4th and 5th space infront of the cannon. After use, the cannon is removed from the board.",
                       350,
                       1);

    activePiece = nullptr;

    isWhitesTurn = true;

    players[1].isWhite = false;

    cursor = new Cursor();
    cursor->SetCursorToWhiteColour(true);
    components.Add(cursor);

    previousTile = nullptr;
    input.Mouse.Pressed = false;
}

void Autochess::Update()
{
    gameBoard->Update();
    shop->Update();

    if (piece1->currentTile == nullptr)
    {
        *piece1->icon->matrix.x = 200;
        *piece1->icon->matrix.y = 430;
        piece1->icon->Update();
    }
    if (piece2->currentTile == nullptr)
    {
        *piece2->icon->matrix.x = 250;
        *piece2->icon->matrix.y = 430;
        piece2->icon->Update();
    }

    if (input.Mouse.Pressed)
    {
        Tile* tile = gameBoard->GetBoardPieceUnderMouse();

        if (tile && activePiece)
        {
            if (activePiece->currentTile)
            {
                activePiece->currentTile->piece = nullptr;
            }

            activePiece->currentTile = tile;
            tile->piece = activePiece;
        }
        if (piece1->currentTile == nullptr)
        {
            if (piece1->icon->IsPressed())
            {
                activePiece = piece1;
            }
        }
        if (piece2->currentTile == nullptr)
        {
            if (piece2->icon->IsPressed())
            {
                activePiece = piece2;
            }
        }
    }

    /*if (input.Mouse.Pressed)
    {
        isWhitesTurn = !isWhitesTurn;

        if (isWhitesTurn)
        {
            activeCursor = whiteCursor;
        }
        else
        {
            activeCursor = blackCursor;
        }
    }*/
}

void Autochess::UpdateAfterPhysics()
{
}
