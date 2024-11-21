#include "replayscene.h"
#include <core/application.h>
#include "main.h"

extern LinkedList<Move> replay;
LinkedList<Move>::Iterator move = replay.Begin();

ReplayScene::ReplayScene()
{

}

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
            (*move).Execute();
        }

        index++;
    }
}

void ReplayScene::LastMove()
{
    if(index > 0)
    {
        if((*move).isPlacement)
        {
            (*move).oldTile->piece = nullptr;
        }
        else
        {
            (*move).Undo();
        }
        --move;
        index--;
    }
}

void ReplayScene::Init()
{
    move = replay.Begin();

    gameBoard = (*move).gameBoard;
    background = (*move).background;

    LinkedList<Tile>::Iterator tile = gameBoard->tiles.Begin();

    for (; tile != NULL; ++tile)
    {
        (*tile).piece = nullptr;
    }

    white   = new Player(true);
    black   = new Player(false);

    blueBanner      = new Sprite("data/FightOfKingsBlueBanner.png", 0, 135, 0.75, 0.75);
    yellowBanner    = new Sprite("data/FightOfKingsYellowBanner.png", 0, 530, 0.75, 0.75);
    turnsLeftBanner = new Sprite("data/FightOfKingsYellowBanner.png", renderer->windowWidth - 140, 135, 0.75, 0.75);
    victoryBanner   = new Sprite("data/victoryBanner.png", renderer->windowWidth / 2 - 250, 250, 0.55, 0.55);

    leftArrow = new Sprite("data/arrow.png", renderer->windowWidth - 120, renderer->windowHeight - 60, 0.5, 0.5);
    leftArrow->FlipHorizontal();
    rightArrow = new Sprite("data/arrow.png", renderer->windowWidth - 60, renderer->windowHeight - 60, 0.5, 0.5);

    backArrow = new Sprite("data/backArrow.png", 10, 10, 0.25, 0.25);

    index = 0;
    cursor = new Cursor();
}

void ReplayScene::Update()
{
    background->Update();
    gameBoard->Update();

    white->nobilityText->Update();
    black->nobilityText->Update();

    white->UpdateNobilityText();
    black->UpdateNobilityText();

    blueBanner->Update();
    yellowBanner->Update();
    turnsLeftBanner->Update();

    if(index > 0)
    {
        leftArrow->Update();
    }

    if(leftArrow->IsPressed())
    {
        LastMove();
    }

    if(index + 1 < replay.count)
    {
        rightArrow->Update();
    }

    if(rightArrow->IsPressed())
    {
        NextMove();
    }

    backArrow->Update();

    if(backArrow->IsPressed())
    {
        Application::LoadScene(Scenes::MainMenu);
    }

    cursor->Update();

    if (input.Pressed(input.Key.ESCAPE))
    {
        Application::LoadScene(Scenes::MainMenu);
    }
    if (input.Pressed(input.Key.RIGHT))
    {
        NextMove();
    }
    if (input.Pressed(input.Key.LEFT))
    {
        LastMove();
    }
}
