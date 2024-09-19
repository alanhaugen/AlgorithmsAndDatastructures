#include <core/application.h>
#include "mainmenu.h"

mainmenu::mainmenu()
{
};

void mainmenu::Init()
{
    cam = new Camera();
    image = new Sprite("data/MainMenuScene.png", -256, -256, 0.5, 0.5);
    cursor = new Sprite("data/BlackCursor.png", -256, -256, 1.0, 1.0);
    cords = new Text("X, Y");
    components.Add(image);
    components.Add(cam);
    components.Add(cursor);
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

    if (input.Mouse.Pressed)
    {
        if ((input.Mouse.x > 123 && input.Mouse.y > 121) &&
            (input.Mouse.x < 380 && input.Mouse.y < 180))
        {
            Application::NextScene();
        }

        if ((input.Mouse.x > 129 && input.Mouse.y > 419) &&
            (input.Mouse.x < 383 && input.Mouse.y < 471))
        {
            Application::Quit();
        }
    }

    *cursor->matrix.x = input.Mouse.x;
    *cursor->matrix.y = input.Mouse.y;

    //delete cords;
    //cords = new Text(String(input.Mouse.x) + ", " + String(input.Mouse.y));
    //cords->Update();
};
