#include <core/application.h>
#include "autochess.h"
#include "main.h"

Autochess::Autochess()
{
}

void Autochess::NextPlayer()
{
    isWhitesTurn = !isWhitesTurn;
    cursor->SetCursorToWhiteColour(isWhitesTurn);
    shop->SetShopPiecesToWhite(isWhitesTurn);

    if (isWhitesTurn)
    {
        activePlayer = white;
    }
    else
    {
        activePlayer = black;
    }
}

void Autochess::Init()
{
    gameBoard = new Board();
    shop      = new Shop();

    white = new Player(true, false);
    black = new Player(false, false);

    players.Add(white);
    players.Add(black);

    isWhitesTurn = true;
    activePlayer = white;

    cursor = new Cursor();
    cursor->SetCursorToWhiteColour(isWhitesTurn);
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
    white->Update();
    black->Update();

    // Finite State Machine (FSM) for gameplay logic
    if (state == GameState::Shopping)
    {
        shop->Update();

        if (input.Mouse.Pressed)
        {
            if (activePlayer->buttonReady->IsPressed())
            {
                activePlayer->isReady = true;

                if (swapPlayers)
                {
                    NextPlayer();
                    swapPlayers = false;
                }
            }

            if (shop->activePiece)
            {
                bool success = false;

                if (activePlayer->gold >= shop->activePiece->price)
                {
                    activePlayer->gold -= shop->activePiece->price;
                    activePlayer->piecesInHand.Append(shop->activePiece);

                    delete activePlayer->goldText;

                    if (activePlayer->isWhite)
                    {
                        activePlayer->goldText = new Text("WHITE GOLD: " + String(activePlayer->gold), 20, 400, 0.4, 0.4);
                    }
                    else
                    {
                        black->goldText = new Text("BLACK GOLD: " + String(activePlayer->gold), 40, 90, 0.4, 0.4);
                    }

                    success = true;
                }

                if (success)
                {
                    shop->items.Remove(shop->activePiece->listNode);
                    shop->activePiece = nullptr;

                    if (swapPlayers)
                    {
                        NextPlayer();
                    }
                }
            }
        }

        if (white->isReady && black->isReady)
        {
            state = GameState::Placing;
        }
    }
    else
    {
        gameBoard->Update();
    }

    if (state == GameState::Placing)
    {
        if (input.Mouse.Pressed)
        {
            Tile* tile = gameBoard->GetBoardTileUnderMouse();

            // Check if user has clicked on an empty tile
            if (tile != nullptr && tile->piece == nullptr)
            {
                // Activate piece from the shop
                if (activePlayer->activePiece)
                {
                    activePiece = activePlayer->activePiece;
                    //activePlayer->piecesInHand.Remove(activePlayer->activePiece->listNode);
                    activePlayer->activePiece = nullptr;

                    NextPlayer();

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
                activePlayer->activePiece = nullptr;
            }
        }
    }
    else if (state == GameState::Playing)
    {
    }
    else if (state == GameState::Done)
    {
    }

    if (input.Pressed(input.Key.ESCAPE))
    {
        Application::LoadScene(Scenes::MainMenu);
    }

}
