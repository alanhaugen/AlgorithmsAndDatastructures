#include "replayscene.h"
#include <core/application.h>
#include "main.h"

extern LinkedList<Move> replay;

ReplayScene::ReplayScene()
{

}

void ReplayScene::Init()
{
    background = new Sprite("data/BackgroundImage.png", 0, 0, 1.78, 1.78);

    gameBoard = new Board();

    white = new Player(true);
    black = new Player(false);

    blueBanner      = new Sprite("data/FightOfKingsBlueBanner.png", 0, 135, 0.75, 0.75);
    yellowBanner    = new Sprite("data/FightOfKingsYellowBanner.png", 0, 530, 0.75, 0.75);
    turnsLeftBanner = new Sprite("data/FightOfKingsYellowBanner.png", renderer->windowWidth - 140, 135, 0.75, 0.75);
    victoryBanner   = new Sprite("data/victoryBanner.png", renderer->windowWidth / 2 - 250, 250, 0.55, 0.55);

    cursor = new Cursor();
}

void ReplayScene::Update()
{
    background->Update();
    gameBoard->Update();

    white->nobilityText->Update();
    black->nobilityText->Update();

    blueBanner->Update();
    yellowBanner->Update();
    turnsLeftBanner->Update();
    cursor->Update();

    if (input.Pressed(input.Key.ESCAPE))
    {
        Application::LoadScene(Scenes::MainMenu);
    }
}
