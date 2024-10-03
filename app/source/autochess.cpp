#include "autochess.h"

autochess::autochess()
{
}

void autochess::Init()
{
    players = Array<Player>(2);
    board = new Board();
    board->Init();
}

void autochess::Update()
{
    board->Update();
}

void autochess::UpdateAfterPhysics()
{
}

