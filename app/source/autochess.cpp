#include <core/application.h>
#include "autochess.h"
#include "main.h"
#include <ctime>
#include <core/containers/linkedlist.h>
#include "replaynew.h"

extern bool isTwoPlayer;
extern bool vsAI;
extern bool isFirstPlaythrough;

extern LinkedList<Move> replay;
extern LinkedList<ReplayNew> replays;

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
        activePlayer   = white;
        opponentPlayer = black;
    }
    else
    {
        activePlayer   = black;
        opponentPlayer = white;
    }
}

void Autochess::Init()
{
    background          = new Sprite("data/BackgroundImage.png", 0, 0, 1.78, 1.78);

    gameBoard           = new Board();

    blackPiecesBanner   = new Sprite("data/DarkBanner.png",  10, 0,   1.35, 0.45);
    whitePiecesBanner   = new Sprite("data/WhiteBanner.png", 10, 655, 1.35, 0.45);

    backArrow           = new Sprite("data/backArrow.png", 10, 10, 0.25, 0.25);
    undoButton          = new Sprite("data/Button-Undo_Move.png", renderer->windowWidth - 350, renderer->windowHeight / 2, 0.5, 0.5);

    shop                = new Shop();

    // Player vs Player
    if (isTwoPlayer == true && vsAI == false)
    {
        white = new Player(true);
        black = new Player(false);
    }
    // AI vs AI
    else if (isTwoPlayer == false && vsAI == true)
    {
        white = new AIPlayer(true);
        black = new AIPlayer(false);
    }
    // Player vs AI
    else if (isTwoPlayer == true && vsAI == true)
    {
        white = new Player(true);
        black = new AIPlayer(false);
    }
    else
    {
        LogError("Invalid configuration");
    }

    players.Add(white);
    players.Add(black);

    isWhitesTurn        = true;
    activePlayer        = white;
    opponentPlayer      = black;

    blueBanner          = new Sprite("data/FightOfKingsBlueBanner.png", 0, 135, 0.75, 0.75);
    yellowBanner        = new Sprite("data/FightOfKingsYellowBanner.png", 0, 530, 0.75, 0.75);
    turnsLeftBanner     = new Sprite("data/FightOfKingsYellowBanner.png", renderer->windowWidth - 140, 135, 0.75, 0.75);
    victoryBanner       = new Sprite("data/victoryBanner.png", renderer->windowWidth / 2 - 250, 250, 0.55, 0.55);

    goldIcon1           = new Sprite("data/gold.png", 100, 140, 0.25, 0.25);
    goldIcon2           = new Sprite("data/gold.png", 100, 540, 0.25, 0.25);

    nobilityIcon1       = new Sprite("data/NobilityIcon.png", 30, 148, 0.25, 0.25);
    nobilityIcon2       = new Sprite("data/NobilityIcon.png", 30, 543, 0.25, 0.25);

    playerWhiteWins     = new Text("PLAYER WHITE WINS!", renderer->windowWidth / 2 - 200,290);
    playerBlackWins     = new Text("PLAYER BLACK WINS!", renderer->windowWidth / 2 - 200,290);
    playerDraw          = new Text("DRAW", renderer->windowWidth / 2 - 200,290);

    playerWhiteTurn     = new Text("Player WHITE make a move", 150,60);
    playerBlackTurn     = new Text("Player BLACK make a move", 150,60);

    input.Mouse.Pressed = false; // hack.

    swapPlayers         = true;
    isAnyWhitePieces    = false;
    isAnyBlackPieces    = false;
    activePiece         = nullptr;

    movesCompleted = 0;
    isDraw = false;
    replayAdded = false;

    movesLeftText       = new Text(String(MovesTotal - movesCompleted), renderer->windowWidth - 120, 165);

    state               = GameState::Shopping;

    topPreviousMoves.Push(new Text("text1"));
    topPreviousMoves.Push(new Text("text2"));
    topPreviousMoves.Push(new Text("text3"));
    topPreviousMoves.Push(new Text("text4"));
    topPreviousMoves.Push(new Text("text5"));

    activeInfoBoard = nullptr;

    cam = new Camera();
    components.Add(cam);

    white->UpdateNobilityText();
    black->UpdateNobilityText();

    replay.Clear();
    Move firstMove;
    firstMove.gameBoard = gameBoard;
    firstMove.background = background;
    replay.Append(firstMove);
    components.Add(background);

    cursor = new Cursor();
    cursor->SetCursorToWhiteColour(isWhitesTurn);
    components.Add(cursor);

    infoBoardTimer = Application::GetTime("Info board timer");
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

    backArrow->Update();

    nobilityIcon1->Update();
    nobilityIcon2->Update();

    if (input.Pressed(input.Key.ESCAPE))
    {
        Application::LoadScene(Scenes::MainMenu);
    }

    if (backArrow->IsPressed())
    {
        Application::LoadScene(Scenes::MainMenu);
    }

    if(undoButton->IsPressed())
    {
        if(state == GameState::Placing && replay.End()->isPlacement == false)
        {
            replay.End()->Undo();
            replay.RemoveAt(replay.count);
        }
    }

    // Finite State Machine (FSM) for gameplay logic
    if (state == GameState::Shopping)
    {
        UpdateShop();
        UpdateInfoBoard();
        UpdateInfoBoardShop();
    }
    else
    {
        gameBoard->Update();
    }

    if (state == GameState::Placing)
    {
        UpdatePlacing();
        UpdateInfoBoard();
    }
    else if (state == GameState::Playing)
    {
        UpdatePlaying();
        UpdateInfoBoard();
    }
    else if (state == GameState::Done)
    {
        UpdateDone();
    }

    if (state == GameState::Animate)
    {
        UpdateAnimation();
    }

    if (activeInfoBoard != nullptr && infoBoardTimer->TimeSinceStarted() < 5000.0f)
    {
        activeInfoBoard->Update();
    }
}

void Autochess::UpdateShop()
{
    shop->Update();

    goldIcon1->Update();
    goldIcon2->Update();

    if(shop->restockShop->IsPressed() == true && activePlayer->gold >= shop->RestockShopCost)
    {
        shop->StockShopFront();
        activePlayer->gold -= shop->RestockShopCost;
        activePlayer->UpdateGoldText();

        if(shop->RestockShopNextPlayer == true && opponentPlayer->isReady == false)
        {
            NextPlayer();
        }
    }

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

                //to update the players nobility before updating the text.
                activePlayer->Update();

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

void Autochess::UpdatePlacing()
{
    gameBoard->highlight->Hide();

    if (activePlayer->activePiece != nullptr)
    {
        //undoButton->Update(); //Button does not work, and not working on it currently.

        isFirstPlaythrough = false;

        movesLeftText->Update();
        //gameBoard->highlight->Show();
        moves.Clear();

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
                replay.Append(Move(tile->piece, tile, true));
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

void Autochess::UpdatePlaying()
{
    // Disable further tutorials
    isFirstPlaythrough = false;

    // Update text
    movesLeftText->Update();

    // Show whose turn it is text
    if (isWhitesTurn)
    {
        playerWhiteTurn->Update();
    }
    else
    {
        playerBlackTurn->Update();
    }

    // Update the current player's hand
    //activePlayer->Update();

    // Use polymorphism to update player <=> Dynamically cast active player to AI player
    AIPlayer* aiPlayer = dynamic_cast<AIPlayer*>(activePlayer);

    Move nextMove;

    // Update AI player if the casting succeeded
    if (aiPlayer != nullptr)
    {
        nextMove = aiPlayer->GetNextMove(gameBoard, opponentPlayer);
    }
    // If casting fails => the player is human. Update human player
    else
    {
        nextMove = activePlayer->GetNextMove(gameBoard);
    }

    // Do the next move
    if (nextMove.movedPiece != nullptr)
    {
        nextMove.Execute();
        replay.Append(nextMove);

        // Add to number of moves counter after white and black has played their turns
        if (isWhitesTurn == false)
        {
            movesCompleted++;
        }

        // Recalculate and show new nobility for the player
        white->RecalculateNobility(gameBoard);
        black->RecalculateNobility(gameBoard);

        // Activate animation of the move
        Animate(nextMove);

        // Go to the next player
        NextPlayer();

        // Update moves left text
        int x = *movesLeftText->matrix.x;
        int y = *movesLeftText->matrix.y;
        delete movesLeftText;
        movesLeftText = new Text(String(MovesTotal - movesCompleted), x, y);

        // Check if the game is over
        state = IsGameDone();
    }

    // Update the game board
    gameBoard->Update();
}

void Autochess::UpdateDone()
{
    white->nobilityText->Update();
    black->nobilityText->Update();

    victoryBanner->Update();

    //time_t timestamp;
    //time(&timestamp);

    //String PlayDate = ctime(&timestamp);

    if (isDraw)
    {
        playerDraw->Update();
        if(!replayAdded)
        {
            replays.Append(ReplayNew(&replay, true, true, "PlayDate"));
        }
    }
    else if (isAnyBlackPieces)
    {
        playerBlackWins->Update();
        if(!replayAdded)
        {
            replays.Append(ReplayNew(&replay, false, false, "PlayDate"));
            Log("Black");
        }
    }
    else if (isAnyWhitePieces)
    {
        playerWhiteWins->Update();
        if(!replayAdded)
        {
            replays.Append(ReplayNew(&replay, false, true, "PlayDate"));
            Log("White");
        }
    }

    replayAdded = true;
}

void Autochess::UpdateAnimation()
{
    if (*animatedMove.movedPiece->icon->matrix.x >= endpos.x -5 && *animatedMove.movedPiece->icon->matrix.y <= endpos.y +5
        && (*animatedMove.movedPiece->icon->matrix.x <= endpos.x+5 && *animatedMove.movedPiece->icon->matrix.y >= endpos.y -5))
    {
        state = GameState::Playing;
        animatedMove.movedPiece->isCurrentlyInAnimation = false;
    }

    float animationSpeed = 5.00f;

    *animatedMove.movedPiece->icon->matrix.x += (endpos - startpos).x / ((endpos - startpos).length() * animationSpeed);
    *animatedMove.movedPiece->icon->matrix.y += (endpos - startpos).y / ((endpos - startpos).length() * animationSpeed);
}

GameState Autochess::IsGameDone()
{
    // The game over states
    if (    black->GetAllPossibleMoves(gameBoard).Empty() == true ||
            white->GetAllPossibleMoves(gameBoard).Empty() == true ||
            movesCompleted >= MovesTotal)
    {
        // Nobility dicates the winner, if they are equal it is a draw
        if (white->nobility == black->nobility)
        {
            isDraw = true;
        }

        // White wins if they have more nobility
        if (white->nobility > black->nobility)
        {
            isAnyWhitePieces = true;
        }

        // Else, black wins if they have more nobility
        else if (white->nobility < black->nobility)
        {
            isAnyBlackPieces = true;
        }

        return GameState::Done;
    }

    // Finish animation first
    if (state == GameState::Animate)
    {
        return GameState::Animate;
    }

    return GameState::Playing;
}

void Autochess::UpdateInfoBoardShop()
{
    LinkedList<Piece*>::Iterator piece = shop->itemsStoreFront.Begin();

    for (; piece != NULL; ++piece)
    {
        if ((*piece)->backgroundCard->IsHoveredOver())
        {
            activeInfoBoard = (*piece)->infoBoard;
            infoBoardTimer->Reset();
        }
    }
}

void Autochess::UpdateInfoBoard()
{
    LinkedList<Piece*>::Iterator piece = white->piecesInHand.Begin();

    for (; piece != NULL; ++piece)
    {
        if ((*piece)->icon->IsHoveredOver())
        {
            activeInfoBoard = (*piece)->infoBoard;
            infoBoardTimer->Reset();
        }
    }

    piece = black->piecesInHand.Begin();

    for (; piece != NULL; ++piece)
    {
        if ((*piece)->icon->IsHoveredOver())
        {
            activeInfoBoard = (*piece)->infoBoard;
            infoBoardTimer->Reset();
        }
    }

    LinkedList<Tile>::Iterator tile = gameBoard->tiles.Begin();

    for (; tile != NULL; ++tile)
    {
        if ((*tile).piece != nullptr)
        {
            if ((*tile).piece->icon->IsHoveredOver())
            {
                activeInfoBoard = (*tile).piece->infoBoard;
                infoBoardTimer->Reset();
            }
        }
    }
}


void Autochess::Animate(Move move)
{
    state = GameState::Animate;
    startpos = glm::vec2(*move.oldTile->sprite->matrix.x, *move.oldTile->sprite->matrix.y);
    endpos = glm::vec2(*move.tileToMoveTo->sprite->matrix.x, *move.tileToMoveTo->sprite->matrix.y);
    *move.movedPiece->icon->matrix.x = startpos.x;
    *move.movedPiece->icon->matrix.y = startpos.y;
    animatedMove = move;
    animatedMove.movedPiece->isCurrentlyInAnimation = true;
}
