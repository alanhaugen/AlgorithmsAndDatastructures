#include <core/application.h>
#include "mainmenu.h"

mainmenu::mainmenu()
{
};

void mainmenu::Init()
{
    cam = new Camera();
    image = new Sprite("data/MainMenuScene.png", -256, -256, 0.5, 0.5);
    cords = new Text("X, Y");
    components.Add(image);
    components.Add(cam);
};

void mainmenu::Update()
{
    if (input.Pressed(input.Key.ENTER))
    {
        Application::NextScene();
    }
    if (input.Pressed(input.Key.ESCAPE))
    {
        Application::Quit();
    }
    delete cords;
    cords = new Text(String(input.Mouse.x) + ", " + String(input.Mouse.y));
    cords->Update();
};
