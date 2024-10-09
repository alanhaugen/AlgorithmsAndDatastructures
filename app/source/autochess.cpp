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

    playerWhiteWins = new Text("PLAYER WHITE WINS!", 50,20, 0.5, 0.5);
    playerBlackWins = new Text("PLAYER BLACK WINS!", 50,20, 0.5, 0.5);

    input.Mouse.Pressed = false;

    time = Application::GetTime("wait time");

    swapPlayers = true;
    isAnyWhitePieces = false;
    isAnyBlackPieces = false;
    activePiece = nullptr;

    state = GameState::Shopping;
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

            if (white->gold > black->gold)
            {
                if (isWhitesTurn == false)
                {
                    NextPlayer();
                }
            }
            else
            {
                if (isWhitesTurn)
                {
                    NextPlayer();
                }
            }
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
                    activePlayer->piecesInHand.Remove(activePlayer->activePiece->listNode);
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

        if (white->piecesInHand.Empty() && black->piecesInHand.Empty())
        {
            state = GameState::Playing;
            Log("Playing!");
        }

        if (activePlayer->piecesInHand.Empty())
        {
            NextPlayer();
        }

    }
    else if (state == GameState::Playing)
    {
        moves.Clear();

        if (time->TimeSinceStarted() < 900.0f)
        {
            return;
        }

        time->Reset();

        isAnyWhitePieces = false;
        isAnyBlackPieces = false;

        LinkedList<Tile>::Iterator tile = gameBoard->tiles.Begin();

        for (; tile != gameBoard->tiles.End(); ++tile)
        {
            if ((*tile).piece != nullptr)
            {
                if ((*tile).piece->isWhite)
                {
                    isAnyWhitePieces = true;
                }
                else if ((*tile).piece->isWhite == false)
                {
                    isAnyBlackPieces = true;
                }

                if ((*tile).piece->isWhite == isWhitesTurn)
                {
                    moves += gameBoard->UpdateDots(&(*tile));
                }
            }
        }

        bool moved = false;

        if (moves.Empty() == false)
        {
            for (unsigned int i = 0; i < moves.Size(); i++)
            {
                if (moves[i].isCapture)
                {
                    moves[i].Execute();
                    moved = true;
                    break;
                }
            }

            if (moved == false)
            {
                moves[random.RandomRange(0, moves.Size())].Execute();
            }
        }

        gameBoard->HideDots();

        NextPlayer();

        if (isAnyWhitePieces == false || isAnyBlackPieces == false)
        {
            state = GameState::Done;
        }
    }
    else if (state == GameState::Done)
    {
        if (isAnyBlackPieces)
        {
            playerBlackWins->Update();
        }
        if (isAnyWhitePieces)
        {
            playerWhiteWins->Update();
        }
    }

    if (input.Pressed(input.Key.ESCAPE))
    {
        Application::LoadScene(Scenes::MainMenu);
    }

}
