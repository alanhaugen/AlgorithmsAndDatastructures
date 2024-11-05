#include "replayscene.h"

ReplayScene::ReplayScene()
{

}

void ReplayScene::Init()
{
    gameBoard = new Board();

    white = new Player(true);
    black = new Player(false);

    blueBanner      = new Sprite("data/FightOfKingsBlueBanner.png", 0, 135, 0.75, 0.75);
    yellowBanner    = new Sprite("data/FightOfKingsYellowBanner.png", 0, 530, 0.75, 0.75);
    turnsLeftBanner = new Sprite("data/FightOfKingsYellowBanner.png", 650, 135, 0.75, 0.75);
    victoryBanner   = new Sprite("data/victoryBanner.png", 100, 250, 0.55, 0.55);

    cursor = new Cursor();
}

void ReplayScene::Update()
{
    gameBoard->Update();

    white->nobilityText->Update();
    black->nobilityText->Update();

    blueBanner->Update();
    yellowBanner->Update();
    turnsLeftBanner->Update();
    cursor->Update();
}
