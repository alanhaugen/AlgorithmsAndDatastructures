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
    piece = new Piece("Rook",
                      "data/Piece-WhiteRook.png",
                      "Rook like in chess",
                      1,
                      0);
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

    if (input.Mouse.Pressed)
    {
        Tile* tile = gameBoard->GetBoardPieceUnderMouse();

        if (tile != nullptr)
        {
            if (piece->currentTile)
            {
                piece->currentTile->piece = nullptr;
            }

            piece->currentTile = tile;
            tile->piece = piece;
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
