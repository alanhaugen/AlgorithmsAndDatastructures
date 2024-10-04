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
    piece1 = new Piece("Rook",
                      "data/Piece-WhiteRook.png",
                      "Rook like in chess",
                      1,
                      0);
    piece2 = new Piece("Rook",
                      "data/Piece-WhiteRook.png",
                      "Rook like in chess",
                      1,
                      0);

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
