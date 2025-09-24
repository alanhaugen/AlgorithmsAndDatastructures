#include "replayscene.h"
#include <core/application.h>
#include "main.h"

extern LinkedList<Move> replay;
LinkedList<Move>::Iterator move = replay.Begin();
extern int MovesTotal;

ReplayScene::ReplayScene(){}

void ReplayScene::NextMove()
{
    if(index + 1 < replay.count)
    {
        ++move;
        if((*move).isPlacement)
        {
            (*move).oldTile->piece = (*move).movedPiece;
        } else
        {
            MovesLeft--;
            (*move).Execute();
            Animate((*move));
        }

        index++;
    }

    gameBoard->HideDots();

}

void ReplayScene::LastMove()
{

    if(index > 0)
    {
        if (state == GameState::Animate)
        {
            animationMoveStack.Clear();
            *animatedMove.movedPiece->icon->matrix.x = *animatedMove.oldTile->sprite->matrix.x;
            *animatedMove.movedPiece->icon->matrix.y = *animatedMove.oldTile->sprite->matrix.y;
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
            state = GameState::Playing;
        }
        if (move.curNode != nullptr)
        {
            if((*move).isPlacement)
            {
                (*move).oldTile->piece = nullptr;
            }
            else
            {
                MovesLeft++;
                (*move).Undo();
            }
            --move;
            index--;
        }
    }

    gameBoard->HideDots();
}

void ReplayScene::Init()
{
    MovesLeft = MovesTotal * 2;
    move            = replay.Begin();

    gameBoard       = (*move).gameBoard;
    background      = (*move).background;

    LinkedList<Tile>::Iterator tile = gameBoard->tiles.Begin();

    for (; tile != NULL; ++tile)
    {
        (*tile).piece = nullptr;
    }

    white           = new Player(true);
    black           = new Player(false);

    blueBanner      = new Sprite("data/FightOfKingsBlueBanner.png", 0, 175, 0.75, 0.75);
    yellowBanner    = new Sprite("data/FightOfKingsYellowBanner.png", 0, renderer->windowHeight-275, 0.75, 0.75);
    turnsLeftBanner = new Sprite("data/FightOfKingsYellowBanner.png", renderer->windowWidth - 70, 135, 0.75, 0.75, glm::vec2(0.5, 0));
    victoryBanner   = new Sprite("data/victoryBanner.png", renderer->windowWidth / 2 - 250, 250, 0.55, 0.55);

    turnsLeftText1      = new Text("Turns", 0, 0, 0.7, 0.7, glm::vec2(0.5, 0));
    turnsLeftText2      = new Text("remaining", 0, 0, 0.7, 0.7, glm::vec2(0.5, 0));
    *turnsLeftText1->matrix.x = *turnsLeftBanner->matrix.x;
    *turnsLeftText1->matrix.y = *turnsLeftBanner->matrix.y + 105;
    *turnsLeftText2->matrix.x = *turnsLeftBanner->matrix.x;
    *turnsLeftText2->matrix.y = *turnsLeftBanner->matrix.y + 120;

    leftArrow       = new Sprite("data/B_ArrowLEFT.png", renderer->windowWidth/2 - 150, renderer->windowHeight - 120, 1, 1);

    rightArrow      = new Sprite("data/B_ArrowLEFT.png", renderer->windowWidth/2 + 32, renderer->windowHeight - 120, 1, 1);
    rightArrow->FlipHorizontal();

    backArrow       = new Sprite("data/backArrow.png", 25, 25, 0.5, 0.5);

    rules    = new Rulebook(false);
    settings = new Settings(false);

    nobilityIcon1       = new Sprite("data/NobilityIcon.png", 32, 190, 0.25, 0.25);
    nobilityIcon2       = new Sprite("data/NobilityIcon.png", 32, renderer->windowHeight - 260, 0.25, 0.25);
    whiteNobilityText   = new Text("White Player Nobility", 0, 0, 0.7, 0.7, glm::vec2(0.2, 0.5));
    blackNobilityText   = new Text("Black Player Nobility", 0, 0, 0.7, 0.7, glm::vec2(0.2, 0.5));

    index           = 0;
    cursor          = new Cursor();

    white->RecalculateNobility(gameBoard);
    black->RecalculateNobility(gameBoard);

    gameBoard->HideDots();

    state = GameState::Playing;

    movesLeftText = new Text(String(MovesTotal), *turnsLeftBanner->matrix.x, 165, 1, 1, glm::vec2(0.5, 0.0));

    animationMoveStack.Clear();
}

void ReplayScene::Update()
{
    background->Update();
    gameBoard->Update(Application::deltaTime);

    white->UpdateNobilityText();
    black->UpdateNobilityText();

    blueBanner->Update();
    yellowBanner->Update();
    turnsLeftBanner->Update();
    nobilityIcon1->Update();
    nobilityIcon2->Update();

    rules->Update(Application::deltaTime);
    settings->Update(Application::deltaTime);

    if(movesLeftText != nullptr)
    {
        delete movesLeftText;
    }

    if(MovesLeft % 2 == 0)
    {
        movesLeftText       = new Text(String(MovesLeft / 2), *turnsLeftBanner->matrix.x, 165, 1, 1, glm::vec2(0.5, 0.0));
    }
    else
    {
        movesLeftText       = new Text(String((MovesLeft + 1) / 2), *turnsLeftBanner->matrix.x, 165, 1, 1, glm::vec2(0.5, 0.0));
    }

    movesLeftText->Update();

    checkForPopUp();

    if (state == GameState::Animate)
    {
        UpdateAnimation();     
    }

    if (turnsLeftBanner->IsHoveredOver() && !PopUpOpen)
    {
        turnsLeftText1->Update();
        turnsLeftText2->Update();
    }

    if(index > 0)
    {
        leftArrow->Update();
    }

    if(leftArrow->IsPressed() && !PopUpOpen)
    {
        LastMove();
    }

    if(index + 1 < replay.count)
    {
        rightArrow->Update();
    }

    if(rightArrow->IsPressed() && !PopUpOpen)
    {
        NextMove();
    }

    backArrow->Update();

    if(backArrow->IsPressed() && !PopUpOpen)
    {
        Application::LoadScene(Scenes::MainMenu);
    }

    cursor->Update();

    if (input.Pressed(input.Key.ESCAPE) && !PopUpOpen)
    {
        Application::LoadScene(Scenes::MainMenu);
    }
    if (input.Pressed(input.Key.RIGHT) && !PopUpOpen)
    {
        NextMove();

        white->RecalculateNobility(gameBoard);
        black->RecalculateNobility(gameBoard);
    }
    if (input.Pressed(input.Key.LEFT) && !PopUpOpen)
    {
        LastMove();

        white->RecalculateNobility(gameBoard);
        black->RecalculateNobility(gameBoard);
    }
}

void ReplayScene::UpdateAfterPhysics()
{
}
