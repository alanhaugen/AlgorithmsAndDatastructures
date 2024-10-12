#include <core/application.h>
#include "autochess.h"
#include "main.h"

extern bool isTwoPlayer;

Autochess::Autochess()
{
}

void Autochess::NextPlayer()
{
    isWhitesTurn = !isWhitesTurn;
    cursor->SetCursorToWhiteColour(isWhitesTurn);

    if (state == GameState::Shopping)
    {
        shop->SetShopPiecesToWhite(isWhitesTurn);
    }

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

    playerWhiteWins = new Text("PLAYER WHITE WINS!", 50,20);
    playerBlackWins = new Text("PLAYER BLACK WINS!", 50,20);
    playerDraw      = new Text("DRAW", 50,20);

    input.Mouse.Pressed = false;

    time = Application::GetTime("wait time");

    swapPlayers = true;
    isAnyWhitePieces = false;
    isAnyBlackPieces = false;
    activePiece = nullptr;

    movesCompleted = 0;
    isDraw = false;

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

    if (input.Pressed(input.Key.ESCAPE))
    {
        Application::LoadScene(Scenes::MainMenu);
    }

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

                    activePlayer->UpdateGoldText();

                    success = true;
                }

                if (success)
                {
                    shop->items.Remove(shop->activePiece->listNode);
                    shop->activePiece = nullptr;

                    activePlayer->UpdateNobilityText();

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

            // Player white starts placeing out pieces
            if (isWhitesTurn == false)
            {
                NextPlayer();
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
                // Activate piece from the player hand
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

            Log("Started Playing a New Game");

            activePiece = nullptr;

            // The player with the most gold remaining gets to play first
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
        else if (activePlayer->piecesInHand.Empty())
        {
            NextPlayer();
        }

    }
    else if (state == GameState::Playing)
    {
        moves.Clear();

        white->nobilityText->Update();
        black->nobilityText->Update();

        if (isTwoPlayer)
        {
            if (input.Mouse.Pressed)
            {
                Tile* clickedTile = gameBoard->GetBoardTileUnderMouse();

                if (clickedTile == nullptr)
                {
                    return;
                }

                // Check if user has clicked on tile with a piece
                if (clickedTile->piece != nullptr)
                {
                    // Activate piece from the player hand
                    if (activePlayer->isWhite == clickedTile->piece->isWhite)
                    {
                        activePiece = clickedTile->piece;
                    }
                }

                if (activePiece != nullptr)
                {
                    LinkedList<Tile>::Iterator tile = gameBoard->tiles.Begin();

                    for (; tile != gameBoard->tiles.End(); ++tile)
                    {
                        if ((*tile).piece != nullptr)
                        {
                            if ((*tile).piece->isWhite == isWhitesTurn)
                            {
                                moves += gameBoard->UpdateDots(&(*tile));
                            }
                        }
                    }

                    for (unsigned int i = 0; i < moves.Size(); i++)
                    {
                        if (moves[i].tileToMoveTo->x == clickedTile->x && moves[i].tileToMoveTo->y == clickedTile->y)
                        {
                            moves[i].Execute();
                            NextPlayer();

                            activePiece = nullptr;

                            moves.Clear();

                            LinkedList<Tile>::Iterator tile = gameBoard->tiles.Begin();

                            for (; tile != gameBoard->tiles.End(); ++tile)
                            {
                                if ((*tile).piece != nullptr)
                                {
                                    if ((*tile).piece->isWhite == isWhitesTurn)
                                    {
                                        moves += gameBoard->UpdateDots(&(*tile));
                                    }
                                }
                            }

                            if (moves.Empty())
                            {
                                isAnyBlackPieces = activePlayer->isWhite;
                                isAnyWhitePieces = !activePlayer->isWhite;
                                state = GameState::Done;
                            }

                            gameBoard->HideDots();

                            return;
                        }
                    }

                    //activePiece = nullptr;
                }
            }

            gameBoard->Update();

            return;
        }

        if (time->TimeSinceStarted() < 900.0f)
        {
            return;
        }

        time->Reset();

        isAnyWhitePieces = false;
        isAnyBlackPieces = false;

        LinkedList<Tile>::Iterator tile = gameBoard->tiles.Begin();

        int nobility = 0;

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
                    nobility += (*tile).piece->nobility;
                    moves += gameBoard->UpdateDots(&(*tile));
                }
            }
        }

        if (isWhitesTurn)
        {
            white->UpdateNobilityText(nobility);
        }
        else
        {
            black->UpdateNobilityText(nobility);
        }

        bool moved = false;

        if (moves.Empty() == false)
        {
            Move newMove;

            for (unsigned int i = 0; i < moves.Size(); i++)
            {
                if (moves[i].isCapture)
                {
                    newMove = moves[i];
                    newMove.Execute();
                    history.Append(newMove);
                    moved = true;
                    break;
                }
            }

            if (moved == false)
            {
                newMove = moves[random.RandomRange(0, moves.Size())];
                newMove.Execute();
                history.Append(newMove);
            }

            if (newMove.isCapture)
            {
                Log(newMove.movedPiece->name +
                    " moved to " +
                    String(newMove.tileToMoveTo->x + 1) +
                    " " +
                    String(newMove.tileToMoveTo->y + 1) +
                    " and captures " +
                    newMove.oldPiece->name);
            }
            else
            {
                Log(newMove.movedPiece->name +
                    " moved to " +
                    String(newMove.tileToMoveTo->x + 1) +
                    " " +
                    String(newMove.tileToMoveTo->y + 1));
            }

            movesCompleted++;
        }

        gameBoard->HideDots();

        NextPlayer();

        if ((isAnyWhitePieces == false || isAnyBlackPieces == false) || movesCompleted >= 50)
        {
            state = GameState::Done;

            if (isAnyWhitePieces == true && isAnyBlackPieces == true)
            {
                isAnyWhitePieces = false;
                isAnyBlackPieces = false;

                if (white->totalNobility > black->totalNobility)
                {
                    isAnyWhitePieces = true;
                }
                else if (white->totalNobility < black->totalNobility)
                {
                    isAnyBlackPieces = true;
                }
                else
                {
                    isDraw = true;
                }
            }

            LinkedList<Move>::Iterator event = history.Begin();

            for (; event != history.End(); ++event)
            {
                /*Log((*event).movedPiece->name +
                    " moved to " +
                    String((*event).tileToMoveTo->x) +
                    " " +
                    String((*event).tileToMoveTo->y));*/
                replay.Enqueue((*event));
            }
        }
    }
    else if (state == GameState::Done)
    {
        if (isDraw)
        {
            playerDraw->Update();
        }
        else if (isAnyBlackPieces)
        {
            playerBlackWins->Update();
        }
        else if (isAnyWhitePieces)
        {
            playerWhiteWins->Update();
        }
    }
}
