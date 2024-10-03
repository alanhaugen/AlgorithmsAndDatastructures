#include <core/application.h>
#include "board.h"

Board::Board()
{
}

void Board::Init()
{
    image = new Sprite("data/BoardScene.png", 0, 0, 0.5, 0.5);
    components.Add(image);
}

void Board::Update()
{
    if (input.Pressed(input.Key.BACKSPACE))
    {
        Application::Quit();
    }

    image->Update();
}
