#include "autochess.h"

Autochess::Autochess()
{
}

void Autochess::Init()
{
    players = Array<Player>(2);
    gameBoard = new Board();
    shop = new Shop();
}

void Autochess::Update()
{
    gameBoard->Update();
    shop->Update();
}

void Autochess::UpdateAfterPhysics()
{
}

