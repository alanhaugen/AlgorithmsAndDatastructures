#include "autochess.h"

autochess::autochess()
{
}

void autochess::Init()
{
    players = Array<Player>(2);
    gameBoard = new Board();
    shop = new Shop();
    gameBoard->Init();
}

void autochess::Update()
{
    gameBoard->Update();
}

void autochess::UpdateAfterPhysics()
{
}

