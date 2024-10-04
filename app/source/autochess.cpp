#include <core/application.h>
#include "autochess.h"

Autochess::Autochess()
{
}

void Autochess::Init()
{
    gameBoard = new Board();
    shop = new Shop();
    players = Array<Player>(2);

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

    if (input.Pressed(input.Key.ESCAPE))
    {
        Application::LoadScene(0);
    }

    if (input.Mouse.Pressed)
    {
        Tile* tile = gameBoard->GetBoardPieceUnderMouse();
        
        if (tile != nullptr && shop->activePiece != nullptr)
        {
            if (shop->activePiece->currentTile != nullptr)
            {
                shop->activePiece->currentTile->piece = nullptr;
            }

            shop->activePiece->currentTile = tile;
            tile->piece = shop->activePiece;
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
