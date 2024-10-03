#include <core/application.h>
#include "board.h"

board::board()
{
};

void board::Init()
{
    cam = new Camera();
    image = new Sprite("data/BoardScene.png", 0, 0, 0.5, 0.5);
    components.Add(image);
    components.Add(cam);
};

void board::Update()
{
    if (input.Pressed(input.Key.BACKSPACE))
    {
        Application::Quit();
    }
};
