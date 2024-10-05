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

    input.Mouse.Pressed = false;
}

void Autochess::SetTile(Tile* tile)
{
    activePiece->currentTile = tile;
    tile->piece = activePiece;
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
        Tile* tile = gameBoard->GetBoardTileUnderMouse();

        // Check if user has clicked on an empty tile
        if (tile != nullptr && tile->piece == nullptr)
        {
            // Activate piece from the shop
            if (shop->activePiece)
            {
                activePiece = shop->activePiece;
                shop->items.Remove(shop->activePiece->listNode);
                shop->activePiece = nullptr;

                isWhitesTurn = !isWhitesTurn;
                cursor->SetCursorToWhiteColour(isWhitesTurn);
                shop->SetShopPiecesToWhite(isWhitesTurn);

                SetTile(tile);
            }

            // Move an activated board piece to tile
            else if (activePiece != nullptr && activePiece->isWhite == isWhitesTurn)
            {
                if (activePiece->currentTile != nullptr)
                {
                    activePiece->currentTile->piece = nullptr;
                }

                SetTile(tile);
            }
        }
        // Activate piece from board
        else if (tile != nullptr)
        {
            activePiece = tile->piece;
            shop->activePiece = nullptr;
        }
    }
}
