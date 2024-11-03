#include <core/application.h>
#include "autochess.h"
#include "main.h"

extern bool isTwoPlayer;
extern bool isFirstPlaythrough;

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

    /*
    if (state == GameState::Placing)
    {
        board->SetBoardPiecesToGreen(isWhitesTurn);
    }
    */

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
    background = new Sprite("data/BackgroundImage.png", 0, 0, 1.78, 1.78);

    gameBoard = new Board();

    blackPiecesBanner = new Sprite("data/DarkBanner.png",  10, 0,   1.35, 0.45);
    whitePiecesBanner = new Sprite("data/WhiteBanner.png", 10, 655, 1.35, 0.45);

    shop = new Shop();

    white = new Player(true);
    black = new Player(false);

    players.Add(white);
    players.Add(black);

    isWhitesTurn = true;
    activePlayer = white;

    blueBanner      = new Sprite("data/FightOfKingsBlueBanner.png", 0, 135, 0.75, 0.75);
    yellowBanner    = new Sprite("data/FightOfKingsYellowBanner.png", 0, 530, 0.75, 0.75);
    turnsLeftBanner = new Sprite("data/FightOfKingsYellowBanner.png", renderer->windowWidth - 160, 135, 0.75, 0.75);
    victoryBanner   = new Sprite("data/victoryBanner.png", renderer->windowWidth / 2 - 250, 250, 0.55, 0.55);

    cursor = new Cursor();
    cursor->SetCursorToWhiteColour(isWhitesTurn);
    components.Add(cursor);

    playerWhiteWins = new Text("PLAYER WHITE WINS!", renderer->windowWidth / 2 - 200,290);
    playerBlackWins = new Text("PLAYER BLACK WINS!", renderer->windowWidth / 2 - 200,290);
    playerDraw      = new Text("DRAW", 220,290);

    playerWhiteTurn = new Text("Player WHITE make a move", 150,60);
    playerBlackTurn = new Text("Player BLACK make a move", 150,60);

    input.Mouse.Pressed = false; // hack.

    time = Application::GetTime("wait time");

    swapPlayers      = true;
    isAnyWhitePieces = false;
    isAnyBlackPieces = false;
    activePiece      = nullptr;

    movesCompleted = 0;
    isDraw = false;

    movesLeftText = new Text(String(movesCompleted), renderer->windowWidth - 140, 165);

    state = GameState::Shopping;

    topPreviousMoves.Push(new Text("text1"));
    topPreviousMoves.Push(new Text("text2"));
    topPreviousMoves.Push(new Text("text3"));
    topPreviousMoves.Push(new Text("text4"));
    topPreviousMoves.Push(new Text("text5"));

    cam = new Camera();
    components.Add(cam);
    components.Add(background);
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

    white->nobilityText->Update();
    black->nobilityText->Update();

    blueBanner->Update();
    yellowBanner->Update();
    turnsLeftBanner->Update();

    whitePiecesBanner->Update();
    blackPiecesBanner->Update();

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

            input.Mouse.Pressed = false;

            if (shop->activePiece != nullptr)
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
                    if (shop->activePiece->listNode != nullptr)
                    {
                        shop->itemsStoreFront.Remove(shop->activePiece->listNode);
                        shop->activePiece = nullptr;
                    }

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
        gameBoard->highlight->Hide();

        if (activePlayer->activePiece != nullptr)
        {
            if (isWhitesTurn)
            {
                activePlayer->activePiece->tileBorderGold->Update();
            }
            else
            {
                activePlayer->activePiece->tileBorderBlue->Update();
            }
        }

        if (input.Mouse.Pressed)
        {
            Tile* tile = gameBoard->GetBoardTileUnderMouse();

            // Check if user has clicked on an empty tile
            if (tile != nullptr && tile->piece == nullptr)
            {
                if (isWhitesTurn && tile->y > 3 )
                {
                    return;
                    //insert onScreenMessage: Invalid tile
                }
                if (isWhitesTurn == false && tile->y < 6 )
                {
                    return;
                    //insert onScreenMessage: Invalid tile
                }

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
        isFirstPlaythrough = false;

        movesLeftText->Update();
        gameBoard->highlight->Show();
        moves.Clear();

        if (isWhitesTurn)
        {
            playerWhiteTurn->Update();
        }
        else
        {
            playerBlackTurn->Update();
        }

        if (isTwoPlayer)
        {
            if (activePiece == nullptr)
            {
                LinkedList<Tile>::Iterator tile = gameBoard->tiles.Begin();

                for (; tile != NULL; ++tile)
                {
                    if ((*tile).piece != nullptr)
                    {
                        if ((*tile).piece->isWhite == isWhitesTurn)
                        {
                            activePiece = (*tile).piece;
                            *gameBoard->highlight->matrix.x = *(*tile).piece->icon->matrix.x;
                            *gameBoard->highlight->matrix.y = *(*tile).piece->icon->matrix.y;
                            gameBoard->UpdateDots(&(*tile), true);
                            break;
                        }
                    }
                }
            }

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
                        gameBoard->HideDots();
                        gameBoard->UpdateDots(clickedTile, true);
                    }
                    else
                    {
                        moves.Clear();
                        gameBoard->HideDots();
                    }
                }
                else
                {
                    moves.Clear();
                    gameBoard->HideDots();
                }

                if (activePiece != nullptr)
                {
                    LinkedList<Tile>::Iterator tile = gameBoard->tiles.Begin();

                    for (; tile != NULL; ++tile)
                    {
                        if ((*tile).piece != nullptr)
                        {
                            if ((*tile).piece->isWhite == isWhitesTurn)
                            {
                                moves += gameBoard->UpdateDots(&(*tile), false);
                            }
                        }
                    }

                    for (unsigned int i = 0; i < moves.Size(); i++)
                    {
                        if ((moves[i].tileToMoveTo->x == clickedTile->x && moves[i].tileToMoveTo->y == clickedTile->y) &&
                            (moves[i].oldTile->x == activePiece->currentTile->x && moves[i].oldTile->y == activePiece->currentTile->y))
                        {
                            moves[i].Execute();
                            NextPlayer();

                            gameBoard->HideDots();

                            activePiece = nullptr;

                            moves.Clear();

                            LinkedList<Tile>::Iterator tile = gameBoard->tiles.Begin();

                            int nobility = 0;

                            for (; tile != NULL; ++tile)
                            {
                                if ((*tile).piece != nullptr)
                                {
                                    if ((*tile).piece->isWhite == isWhitesTurn)
                                    {
                                        nobility += tile->piece->nobility;
                                        moves += gameBoard->UpdateDots(&(*tile), false);
                                    }
                                }
                            }

                            if (moves.Empty())
                            {
                                isAnyBlackPieces = activePlayer->isWhite;
                                isAnyWhitePieces = !activePlayer->isWhite;
                                state = GameState::Done;
                            }

                            if (isWhitesTurn)
                            {
                                white->UpdateNobilityText(nobility);
                            }
                            else
                            {
                                black->UpdateNobilityText(nobility);
                            }


                            gameBoard->Update();

                            return;
                        }
                    }
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

        for (; tile != NULL; ++tile)
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
                    moves += gameBoard->UpdateDots(&(*tile), false);
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

                if (isWhitesTurn)
                {
                    white->UpdateNobilityText(nobility);
                }
                else
                {
                    black->UpdateNobilityText(nobility);
                }

                activePlayer->piecesInHand.Append(newMove.movedPiece);
            }
            else
            {
                Log(newMove.movedPiece->name +
                    " moved to " +
                    String(newMove.tileToMoveTo->x + 1) +
                    " " +
                    String(newMove.tileToMoveTo->y + 1));
            }
        }

        gameBoard->HideDots();

        NextPlayer();
        movesCompleted++;

        int x = *movesLeftText->matrix.x;
        int y = *movesLeftText->matrix.y;
        delete movesLeftText;
        movesLeftText = new Text(String(MovesTotal - movesCompleted), x, y);
        movesLeftText->Update();

        if ((isAnyWhitePieces == false || isAnyBlackPieces == false) || movesCompleted >= MovesTotal)
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

            if (history.Empty() == false)
            {
                LinkedList<Move>::Iterator event = history.Begin();

                for (; event != NULL; ++event)
                {
                    /*Log((*event).movedPiece->name +
                        " moved to " +
                        String((*event).tileToMoveTo->x) +
                        " " +
                        String((*event).tileToMoveTo->y));*/
                    // replay.Enqueue((*event));
                }
            }
        }
    }
    else if (state == GameState::Done)
    {
        white->nobilityText->Update();
        black->nobilityText->Update();

        victoryBanner->Update();

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
