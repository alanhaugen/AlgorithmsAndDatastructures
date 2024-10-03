#include <core/application.h>
#include "board.h"

Board::Board()
{
}

void Board::Init()
{
    background = new Sprite("data/BoardScene.png", 0, 0, 0.5, 0.5);
    components.Add(background);
}

void Board::Update()
{
    if (input.Pressed(input.Key.BACKSPACE))
    {
        Application::Quit();
    }

    background->Update();
}
