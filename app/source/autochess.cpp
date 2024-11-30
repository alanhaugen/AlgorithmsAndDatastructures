#include <core/application.h>
#include "autochess.h"
#include "main.h"
#include <core/containers/linkedlist.h>
#include "replaynew.h"
#include <ctime>

extern bool isTwoPlayer;
extern bool vsAI;
extern bool isFirstPlaythrough;

extern LinkedList<Move> replay;
extern LinkedList<ReplayNew> replays;

extern int MovesTotal;

Autochess::Autochess()
{
}

void Autochess::checkForPopUp(){

    if(settings->isOpen)
    {
        rules->canOpen = false;
    }
    else if(rules->isOpen)
    {
        settings->canOpen = false;
    }
    else
    {
        settings->canOpen = true;
        rules->canOpen = true;
    }

    PopUpOpen = (settings->isOpen || rules->isOpen);

    if(shop != nullptr)
    {
        shop->PopUpOpen = PopUpOpen;
    }
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

    gameBoard->HideDots();
}

void Autochess::Init()
{
    background          = new Sprite("data/BackgroundImage.png", 0, 0, 1.78, 1.78);

    gameBoard           = new Board();

    blackPiecesBanner   = new Sprite("data/BannerPiecesTop.png",  renderer->windowWidth / 2, 0, 1, 1, glm::vec2(0.5, 0));
    whitePiecesBanner   = new Sprite("data/BannerPiecesBottom.png", renderer->windowWidth / 2, renderer->windowHeight, 1, 1, glm::vec2(0.5, 1));
    goldBackground      = new Sprite("data/BannerGOLDBackground2.png", 160, renderer->windowHeight - 95, 1.5, 1.5, glm::vec2(0.5, 1));
    goldBackground2     = new Sprite("data/BannerGOLDBackground3.png", 160, 192, 1.5, 1.5, glm::vec2(0.5, 1));

    backArrowText       = new Text("Return",0, 0, 0.8, 0.8, glm::vec2(0.2, 0.5));
    undoButtonText      = new Text("Undo",0, 0, 0.8, 0.8, glm::vec2(0.5, 1));
    backArrow           = new Sprite("data/backArrow.png", 50, 15, 0.5, 0.5);
    undoButton          = new Sprite("data/Button-Undo_Move.png", renderer->windowWidth - 350, renderer->windowHeight - 200, 0.5, 0.5);
    autoPlacePieces     = new Sprite("data/B_Autoplace.png", renderer->windowWidth - 350, renderer->windowHeight / 2, 0.5, 0.5);
    autoPlaceAllPieces  = new Sprite("data/B_AutoplaceAll.png", renderer->windowWidth - 350, (renderer->windowHeight / 2)-100, 0.5, 0.5);
    autoPlaceObstacles  = new Sprite("data/B_PlaceObstacles.png", renderer->windowWidth - 350, (renderer->windowHeight / 2)+100, 0.5, 0.5);
    shop                = new Shop();

    volumeControl       = new Sprite("data/VolumeIcon.png", 0,0,0,0,glm::vec2(0,9));

    audio->Stop();
    int randomNumber = random.RandomRange(0, 3);

    switch(randomNumber)
    {
    case 0:
        audio->PlaySound("data/sound-theme01.wav", Audio::MUSIC);
        break;

    case 1:
        audio->PlaySound("data/sound-theme02.wav", Audio::MUSIC);
        break;

    case 2:
        audio->PlaySound("data/sound-theme03.wav", Audio::MUSIC);
        break;

    case 3:
        audio->PlaySound("data/sound-battleTheme01.wav", Audio::MUSIC);
        break;
    }



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

    firstUpdateInPlaying = true;

    isWhitesTurn        = true;
    activePlayer        = white;
    opponentPlayer      = black;

    blueBanner          = new Sprite("data/FightOfKingsBlueBanner.png", 0, 175, 0.75, 0.75);
    yellowBanner        = new Sprite("data/FightOfKingsYellowBanner.png", 0, renderer->windowHeight-275, 0.75, 0.75);
    turnsLeftBanner     = new Sprite("data/FightOfKingsYellowBanner.png", renderer->windowWidth - 60, 135, 0.75, 0.75, glm::vec2(0.5, 0));
    turnsLeftText1      = new Text("Turns", 0, 0, 0.7, 0.7, glm::vec2(0.5, 0));
    turnsLeftText2      = new Text("remaining", 0, 0, 0.7, 0.7, glm::vec2(0.5, 0));
    *turnsLeftText1->matrix.x = *turnsLeftBanner->matrix.x;
    *turnsLeftText1->matrix.y = *turnsLeftBanner->matrix.y + 105;
    *turnsLeftText2->matrix.x = *turnsLeftBanner->matrix.x;
    *turnsLeftText2->matrix.y = *turnsLeftBanner->matrix.y + 120;
    //victoryBanner       = new Sprite("data/victoryBanner.png", renderer->windowWidth / 2, renderer->windowHeight / 2, 0.55, 0.55, glm::vec2(0.5, 0.5));
    victoryBanner       = new Sprite("data/VictoryScreenGradient.png", renderer->windowWidth / 2, renderer->windowHeight / 2, 1, 1, glm::vec2(0.5, 0.5));
    victoryBanner2      = new Sprite("data/victoryBannerGoldBlue.png", renderer->windowWidth / 2, renderer->windowHeight / 2, 1, 1, glm::vec2(0.5, 0.5));

    goldIcon1           = new Sprite("data/gold.png", 100, 105, 0.25, 0.25);
    goldIcon2           = new Sprite("data/gold.png", 100, renderer->windowHeight - 135, 0.25, 0.25);

    nobilityIcon1       = new Sprite("data/NobilityIcon.png", 32, 190, 0.25, 0.25);
    nobilityIcon2       = new Sprite("data/NobilityIcon.png", 32, renderer->windowHeight - 260, 0.25, 0.25);
    whiteNobilityText   = new Text("White Player Nobility", 0, 0, 0.7, 0.7, glm::vec2(0.2, 0.5));
    blackNobilityText   = new Text("Black Player Nobility", 0, 0, 0.7, 0.7, glm::vec2(0.2, 0.5));

    playerWhiteWins     = new Text("PLAYER WHITE WINS!", renderer->windowWidth / 2, renderer->windowHeight / 2, 1, 1, glm::vec2(0.5, 0.5));
    playerBlackWins     = new Text("PLAYER BLACK WINS!", renderer->windowWidth / 2, renderer->windowHeight / 2, 1, 1, glm::vec2(0.5, 0.5));
    playerDraw          = new Text("DRAW", renderer->windowWidth / 2, renderer->windowHeight / 2, 1, 1, glm::vec2(0.5, 0.5));

    playerWhiteTurn     = new Text("Player WHITE make a move", renderer->windowWidth*0.705, renderer->windowHeight - 150);
    playerBlackTurn     = new Text("Player BLACK make a move", renderer->windowWidth*0.705, renderer->windowHeight - 150);

    input.Mouse.Pressed = false; // hack.

    swapPlayers         = true;
    isAnyWhitePieces    = false;
    isAnyBlackPieces    = false;
    activePiece         = nullptr;

    movesCompleted      = 0;
    isDraw              = false;
    replayAdded         = false;

    movesLeftText       = new Text(String(MovesTotal - movesCompleted), *turnsLeftBanner->matrix.x, 165, 1, 1, glm::vec2(0.5, 0.0));

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
    firstMove.gameBoard     = gameBoard;
    firstMove.background    = background;
    replay.Append(firstMove);
    components.Add(background);

    returnToMainMenu        = new Sprite("data/B_BackToMain.png", renderer->windowWidth / 2,
                                  renderer->windowHeight / 2 + 100,0.5,0.5, glm::vec2(0.5, 0.5));
    watchReplay             = new Sprite("data/B_WatchReplay.png", renderer->windowWidth / 2,
                                  renderer->windowHeight / 2 + 180,0.5,0.5, glm::vec2(0.5, 0.5));

    rules                   = new Rulebook(false);
    settings                = new Settings(false);



    infoBoardTimer          = Application::GetTime("Info board timer");

    cursor                  = new Cursor();
    cursor->SetCursorToWhiteColour(isWhitesTurn);
    components.Add(cursor);
}

void Autochess::SetTile(Tile* tile)
{
    activePiece->currentTile = tile;
    tile->piece = activePiece;
}

void Autochess::Update()
{
    if (volumeControl->IsPressed())
    {

        audio->PlaySound("data/sound-theme01.wav", Audio::MUSIC);

    }

    white->Update();
    black->Update();

    goldIcon1->Update();
    goldIcon2->Update();

    white->nobilityText->Update();
    black->nobilityText->Update();

    blueBanner->Update();
    yellowBanner->Update();

    checkForPopUp();

    if(state != GameState::Shopping)
    {
        turnsLeftBanner->Update();
    }

    whitePiecesBanner->Update();
    blackPiecesBanner->Update();
    goldBackground->Update();
    goldBackground2->Update();

    backArrow->Update();

    nobilityIcon1->Update();
    nobilityIcon2->Update();

    rules->Update();
    settings->Update();

    if (input.Pressed(input.Key.ESCAPE) && !PopUpOpen)
    {
        Application::LoadScene(Scenes::MainMenu);
    }

    if (backArrow->IsPressed() && !PopUpOpen)
    {
        Application::LoadScene(Scenes::MainMenu);
    }

    if (backArrow->IsHoveredOver())
    {
        *backArrowText->matrix.x = *backArrow->matrix.x;
        *backArrowText->matrix.y = *backArrow->matrix.y + 70;
        backArrowText->Update();
    }



    if (nobilityIcon2->IsHoveredOver() && !PopUpOpen)
    {
        *whiteNobilityText->matrix.x = *nobilityIcon2->matrix.x + 20;
        *whiteNobilityText->matrix.y = *nobilityIcon2->matrix.y + 90;
        whiteNobilityText->Update();
    }

    if (nobilityIcon1->IsHoveredOver() && !PopUpOpen)
    {
        *blackNobilityText->matrix.x = *nobilityIcon1->matrix.x + 20;
        *blackNobilityText->matrix.y = *nobilityIcon1->matrix.y - 30;
        blackNobilityText->Update();
    }

    if (turnsLeftBanner->IsHoveredOver() && state != GameState::Shopping && !PopUpOpen)
    {
        turnsLeftText1->Update();
        turnsLeftText2->Update();
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

    //Undo-button
    if(replay.count > 1 && state != GameState::Shopping && state != GameState::Done)
    {
        undoButton->Update(); //Button does not work, and not working on it currently.
    }

    if(undoButton->IsPressed() && !PopUpOpen && replay.count > 1 && state != GameState::Shopping && state != GameState::Done)
    {
        if(replay.End()->isPlacement == false)
        {
            replay.End()->Undo();
            replay.Remove(replay.End().curNode);
        }

        else if(replay.End()->isPlacement == true)
        {
            Log("we got here at least");
            if(activePlayer->isWhite && replay.End()->oldTile->piece->isWhite == false)
            {
                black->piecesInHand.Append(replay.End()->oldTile->piece);
            }
            else if(activePlayer->isWhite && replay.End()->oldTile->piece->isWhite)
            {
                white->piecesInHand.Append(replay.End()->oldTile->piece);
                NextPlayer();
            }
            else if(activePlayer->isWhite == false && replay.End()->oldTile->piece->isWhite)
            {
                white->piecesInHand.Append(replay.End()->oldTile->piece);
            }
            else
            {
                black->piecesInHand.Append(replay.End()->oldTile->piece);
                NextPlayer();
            }
            replay.End()->oldTile->piece = nullptr;
            replay.Remove(replay.End().curNode);
            if(state == GameState::Playing)
            {
                state = GameState::Placing;
            }
        }

        NextPlayer();

        if (firstPlayer != activePlayer && isFirstPlaythrough == false && state != GameState::Placing)
        {
            movesCompleted--;
        }
    }

    if (undoButton->IsHoveredOver() && !PopUpOpen && replay.count > 1 && state != GameState::Shopping && state != GameState::Done)
    {
        *undoButtonText->matrix.x = *undoButton->matrix.x;
        *undoButtonText->matrix.y = *undoButton->matrix.y - 70;
        undoButtonText->Update();
    }
}

void Autochess::UpdateShop()
{
    shop->Update();

    if(shop->restockShop->IsPressed() == true && activePlayer->gold >= shop->RestockShopCost && !PopUpOpen && shop->shopItems.Empty() == false)
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
        if (activePlayer->buttonReady->IsPressed() && !PopUpOpen)
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
    autoPlacePieces->Update();
    autoPlaceAllPieces->Update();

    if (shop->obstacleCards.Empty() != true)
    {
        autoPlaceObstacles->Update();
    }

    white->RescalePiecesPlacing();
    black->RescalePiecesPlacing();

    //Auto Place One Piece at the time
    if (autoPlacePieces->IsPressed() && !PopUpOpen)
    {
        if (activePlayer->isWhite == true)
        {
            activePiece = *activePlayer->piecesInHand.Begin();
            Tile*tile = nullptr;
            while (tile == nullptr)
            {
                tile = gameBoard->GetTile(random.RandomRange(0,10), random.RandomRange(0,3));
                if (tile->piece != nullptr)
                {
                    tile = nullptr;
                }
            }

            SetTile(tile);
            activePlayer->piecesInHand.Remove(activePlayer->activePiece->listNode);
            activePlayer->activePiece = nullptr;
            replay.Append(Move(tile->piece, tile, true));
            NextPlayer();
        }
        else
        {
            activePiece = *activePlayer->piecesInHand.Begin();
            Tile*tile = nullptr;
            while (tile == nullptr)
            {
                tile = gameBoard->GetTile(random.RandomRange(0,9), random.RandomRange(6,9));
                if (tile->piece != nullptr)
                {
                    tile = nullptr;
                }
            }

            SetTile(tile);
            activePlayer->piecesInHand.RemoveAt(0);
            activePlayer->activePiece = nullptr;
            replay.Append(Move(tile->piece, tile, true));
            NextPlayer();
        }
    }

    //Auto Place All Pieces
    if (autoPlaceAllPieces->IsPressed() && !PopUpOpen)
    {
        int total = white->piecesInHand.Size() + black->piecesInHand.Size();

        for (int i = 0; i < total; i++)
        {
            if(activePlayer->piecesInHand.Empty())
            {
                NextPlayer();
                continue;
            }
            activePiece = *activePlayer->piecesInHand.Begin();
            Tile*tile = nullptr;
            while (tile == nullptr)
                {
                    if(isWhitesTurn)
                    {
                        tile = gameBoard->GetTile(random.RandomRange(0,10), random.RandomRange(0,4));
                    }
                    else
                    {
                        tile = gameBoard->GetTile(random.RandomRange(0,10), random.RandomRange(6,10));
                    }
                    if (tile->piece != nullptr)
                    {
                        tile = nullptr;
                    }
                }
            SetTile(tile);
            activePlayer->piecesInHand.RemoveAt(0);
            activePlayer->activePiece = nullptr;
            replay.Append(Move(tile->piece, tile, true));
            total++;
            NextPlayer();
        }
    }

    if (autoPlaceObstacles->IsPressed() && shop->obstacleCards.Empty() != true)
    {

        for (int i = 0; i < 6; i++)
        {
            activePiece = *shop->obstacleCards.Begin();
            Tile*tile = nullptr;
            while (tile == nullptr && shop->obstacleCards.Empty() != true)
            {
                //tile = gameBoard->GetTile(random.RandomRange(0,9), random.RandomRange(0,9));


                if (shop->obstacleCards.count > 3)
                {
                    tile = gameBoard->GetTile(random.RandomRange(1,8), random.RandomRange(1,4));
                }
                else
                {
                    tile = gameBoard->GetTile(random.RandomRange(1,8), random.RandomRange(5,8));
                }


                if (tile->piece != nullptr)
                {
                    tile = nullptr;
                    continue;
                }

                SetTile(tile);
                shop->obstacleCards.RemoveAt(0);
                activePiece = nullptr;
                replay.Append(Move(tile->piece, tile, true));
            }


        }

    }

    if (activePlayer->activePiece != nullptr)
    {

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

        firstPlayer = activePlayer;
    }
    else if (activePlayer->piecesInHand.Empty())
    {
        NextPlayer();
    }
}

void Autochess::UpdatePlaying()
{
    // Check if a player has played himself by choosing a piece with no moves as only piece
    if (firstUpdateInPlaying)
    {
        state = IsGameDone();
        firstUpdateInPlaying = false;
    }

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
        nextMove = aiPlayer->GetNextMove(gameBoard, opponentPlayer, MovesTotal == (MovesTotal - movesCompleted));
    }
    // If casting fails => the player is human. Update human player
    else
    {
        nextMove = activePlayer->GetNextMove(gameBoard, MovesTotal == (MovesTotal - movesCompleted));
    }

    // Do the next move
    if (nextMove.movedPiece != nullptr)
    {
        nextMove.Execute();
        replay.Append(nextMove);

        // Add to number of moves counter after white and black has played their turns
        if (firstPlayer != activePlayer && isFirstPlaythrough == false)
        {
            movesCompleted++;
        }

        // Disable further tutorials
        isFirstPlaythrough = false;

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
        movesLeftText = new Text(String(MovesTotal - movesCompleted), x, y, 1, 1, glm::vec2(0.5, 0));

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
    victoryBanner2->Update();
    returnToMainMenu->Update();
    watchReplay->Update();

    if (returnToMainMenu->IsPressed() == true && !PopUpOpen)
    {
        Application::LoadScene(Scenes::MainMenu);
    }
    if (watchReplay->IsPressed() == true && !PopUpOpen)
    {
        Application::LoadScene(Scenes::Replay);
    }

    if (isDraw)
    {
        playerDraw->Update();
        if(!replayAdded)
        {
            time_t timestamp = std::time(NULL);
            String PlayDate = ctime(&timestamp);
            replays.Append(ReplayNew(&replay, true, true, PlayDate));
        }
    }
    else if (isAnyBlackPieces)
    {
        playerBlackWins->Update();
        if(!replayAdded)
        {
            time_t timestamp = std::time(NULL);
            String PlayDate = ctime(&timestamp);
            replays.Append(ReplayNew(&replay, false, false, PlayDate));
        }
    }
    else if (isAnyWhitePieces)
    {
        playerWhiteWins->Update();
        if(!replayAdded)
        {
            time_t timestamp = std::time(NULL);
            String PlayDate = ctime(&timestamp);
            replays.Append(ReplayNew(&replay, false, true, PlayDate));
            Log(PlayDate);
        }
    }

    replayAdded = true;
}

void Autochess::UpdateAnimation()
{
    // Update text
    if (movesLeftText != nullptr)
    {
        movesLeftText->Update();
    }

    // Update animations
    if (animatedMove.captureTile1 != nullptr)
    {
        if (animatedMove.movedPiece->animatedForm != nullptr)
        {
            if (animatedMove.movedPiece->isWhite)
            {
                animatedMove.movedPiece->iconWhite->Update();
            }
            else
            {
                animatedMove.movedPiece->iconBlack->Update();
            }
        }
    }

    if (    *animatedMove.movedPiece->icon->matrix.x >= nextpos.x -5 && *animatedMove.movedPiece->icon->matrix.y <= nextpos.y +5
        && (*animatedMove.movedPiece->icon->matrix.x <= nextpos.x +5 && *animatedMove.movedPiece->icon->matrix.y >= nextpos.y -5))
    {
        prevpos = nextpos;
        nextpos = animationMoveStack.Pop();
    }

    if (animationMoveStack.Empty() == true)
    {
        state = GameState::Playing;
        state = IsGameDone();
        animatedMove.movedPiece->isCurrentlyInAnimation = false;

        if (animatedMove.movedPiece->animatedForm != nullptr)
        {
            if (animatedMove.movedPiece->isWhite)
            {
                animatedMove.movedPiece->icon = animatedMove.movedPiece->iconWhite;
            }
            else
            {
                animatedMove.movedPiece->icon = animatedMove.movedPiece->iconBlack;
            }
        }
    }

    float animationSpeed = 2.50f;

    *animatedMove.movedPiece->icon->matrix.x += (nextpos - prevpos).x / ((nextpos - prevpos).length() * animationSpeed);
    *animatedMove.movedPiece->icon->matrix.y += (nextpos - prevpos).y / ((nextpos - prevpos).length() * animationSpeed);
}

GameState Autochess::IsGameDone()
{
    if (state==GameState::Animate)
    {
        return GameState::Animate;
    }

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
        if ((*piece)->backgroundCard->IsHoveredOver() && !PopUpOpen)
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
        if ((*piece)->icon->IsHoveredOver() && !PopUpOpen)
        {
            activeInfoBoard = (*piece)->infoBoard;
            infoBoardTimer->Reset();
        }
    }

    piece = black->piecesInHand.Begin();

    for (; piece != NULL; ++piece)
    {
        if ((*piece)->icon->IsHoveredOver() && !PopUpOpen)
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
            if ((*tile).piece->icon->IsHoveredOver() && !PopUpOpen)
            {
                activeInfoBoard = (*tile).piece->infoBoard;
                infoBoardTimer->Reset();
            }
        }
    }
}


void Autochess::Animate(Move move)
{
    if (state == GameState::Animate)
    {
        animationMoveStack.Clear();
        *animatedMove.movedPiece->icon->matrix.x = *animatedMove.tileToMoveTo->sprite->matrix.x;
        *animatedMove.movedPiece->icon->matrix.y = *animatedMove.tileToMoveTo->sprite->matrix.y;

        if (animatedMove.movedPiece->animatedForm != nullptr)
        {
            if (animatedMove.movedPiece->isWhite)
            {
                animatedMove.movedPiece->icon = animatedMove.movedPiece->iconWhite;
            }
            else
            {
                animatedMove.movedPiece->icon = animatedMove.movedPiece->iconBlack;
            }
        }
    }

    state = GameState::Animate;

    animatedMove = move;
    animatedMove.movedPiece->isCurrentlyInAnimation = true;

    if (animatedMove.captureTile1 != nullptr)
    {
        if (animatedMove.movedPiece->animatedForm != nullptr)
        {
            animatedMove.movedPiece->icon = animatedMove.movedPiece->animatedForm;
        }
    }

    // Setup positions for animation
    prevpos = glm::vec2(*move.oldTile->sprite->matrix.x, *move.oldTile->sprite->matrix.y);
    nextpos = glm::vec2(*move.tileToMoveTo->sprite->matrix.x, *move.tileToMoveTo->sprite->matrix.y);
    *move.movedPiece->icon->matrix.x = prevpos.x;
    *move.movedPiece->icon->matrix.y = prevpos.y;

    // Added twice to make sure animation finishes for the last position
    animationMoveStack.Push(nextpos);
    animationMoveStack.Push(nextpos);

    // We will not do any fancy A* animations for jumping pieces
    if ((animatedMove.movedPiece->name == String("Deserter") || animatedMove.movedPiece->name == String("Monster")) == false)
    {
        return;
    }

    // Fill stack with positions with the help of A*
    LinkedList<Tile>* tiles = &gameBoard->tiles;
    LinkedList<Tile>::Iterator node = tiles->Begin();

    Piece* piece = animatedMove.movedPiece;
    Tile* startTile = animatedMove.oldTile;
    Tile* endTile   = animatedMove.tileToMoveTo;

    int yDirectionInvert = 1;

    if (piece->isWhite == false)
    {
        yDirectionInvert = -1;
    }

    // Calculate tile weights
    for (; node != NULL; ++node)
    {
        if ((*node).piece != nullptr)
        {
            if ((*node).piece->isWhite != piece->isWhite &&(*node).piece->weightPattern.Empty() == false)
            {
                Array<glm::vec2> weightPattern = (*node).piece->weightPattern;

                LinkedList<Tile>::Iterator newNode = tiles->Begin();

                int x = (*node).x;
                int y = (*node).y;

                for (; newNode != NULL; ++newNode)
                {
                    // Add weight to board
                    for (unsigned int i = 0; i < weightPattern.Size(); i++)
                    {
                        if ((*newNode).x == x + weightPattern[i].x && (*newNode).y == y + (-yDirectionInvert * weightPattern[i].y))
                        {
                            (*newNode).weight = 1;
                        }
                    }
                }
            }
        }
    }

    // A* starts here.
    Tree<Tile*> searchTree;
    Array<Tile*> searchTiles;
    bool isDone = false;

    Tile* currentTile = NULL;

    searchTiles.Add(startTile);

    // We will try to find the smallest F (inits to 0 in Tile)
    int smallestF = -1;

    activeNode = NULL;

    while (isDone == false)
    {
        // Reset smallest F counter
        smallestF = 100000;

        // Get the search tile with the lowest F score
        for (unsigned int i = 0; i < searchTiles.Size(); i++)
        {
            if (searchTiles[i]->visited == false)
            {
                if (smallestF > searchTiles[i]->F)
                {
                    smallestF = searchTiles[i]->F;
                    currentTile = searchTiles[i];
                }
            }
        }

        // Set current tile as visited
        if (currentTile != NULL)
        {
            currentTile->visited = true;

            if (currentTile->searched == true)
            {
                activeNode = currentTile->node;
            }
            else
            {
                // Add current tile to search tree
                activeNode = searchTree.AddNode(currentTile);
                currentTile->node = activeNode;
            }
        }

        // Search current tile
        searchTile(currentTile, startTile, endTile, isDone, searchTiles, searchTree);

        // Look around the tile
        Tile* north = gameBoard->GetTile(currentTile->x, currentTile->y - 1);
        Tile* south = gameBoard->GetTile(currentTile->x, currentTile->y + 1);
        Tile* east  = gameBoard->GetTile(currentTile->x + 1, currentTile->y);
        Tile* west  = gameBoard->GetTile(currentTile->x - 1, currentTile->y);

        if (piece->name == String("Deserter"))
        {
            north = gameBoard->GetTile(currentTile->x - 1, currentTile->y - 1);
            south = gameBoard->GetTile(currentTile->x - 1, currentTile->y + 1);
            east  = gameBoard->GetTile(currentTile->x + 1, currentTile->y - 1);
            west  = gameBoard->GetTile(currentTile->x + 1, currentTile->y + 1);
        }

        // Add new search tiles
        searchTile(north, startTile, endTile, isDone, searchTiles, searchTree);
        searchTile(south, startTile, endTile, isDone, searchTiles, searchTree);
        searchTile(east, startTile, endTile, isDone, searchTiles, searchTree);
        searchTile(west, startTile, endTile, isDone, searchTiles, searchTree);
    }

    // Go back through the tree and add positions to move through to the animation stack
    while (activeNode != NULL)
    {
        animationMoveStack.Push(glm::vec2(*activeNode->data->sprite->matrix.x, *activeNode->data->sprite->matrix.y));
        activeNode = activeNode->parent;
    }

    // Revert board state (weights and search state)
    for (node = tiles->Begin(); node != NULL; ++node)
    {
        (*node).searched = false;
        (*node).visited  = false;
        (*node).weight   = 0;
    }

    // Set the first move
    nextpos = animationMoveStack.Pop();
}

void Autochess::searchTile(Tile *tile, Tile* startTile, Tile* endTile, bool &isDone, Array<Tile*>& searchTiles, Tree<Tile*>& searchTree)
{
    if (tile != nullptr)
    {
        // Add to search list
        if (isDone == false && tile->searched == false)
        {
            Tree<Tile*>::Node* newNode = searchTree.AddNode(tile);
            newNode->parent = activeNode;
            tile->node = newNode;

            searchTiles.Add(tile);
        }

        // Stop search when end tile is found
        if (tile == endTile)
        {
            isDone = true;
        }

        // G is Distance from Node to Start Node
        float G = tile->ManhattenDistanceToOrigin(startTile->x, startTile->y);

        // F is Distance from Node to End Node
        float H = tile->ManhattenDistanceToOrigin(endTile->x, endTile->y);

        // Set F = G + H
        tile->F = (G + H) + (tile->weight * 100);

        // Avoid tiles with pieces
        if (tile->piece != nullptr)
        {
            tile->F *= 100;
        }

        // Set the tile as searched
        tile->searched = true;
    }
}
