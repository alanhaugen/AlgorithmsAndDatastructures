#include "autochess.h"

autochess::autochess()
{
}

void autochess::Init()
{
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

