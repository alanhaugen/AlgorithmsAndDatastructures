#include <core/application.h>
#include "mainmenu.h"
#include "menu.h"

mainmenu::mainmenu()
{
};

void mainmenu::Init()
{
    cam = new Camera();

    Menu* firstMenu = new Menu();
    firstMenu->SetBackground("data/BackgroundImage.png");
    firstMenu->AddNextSceneButton("data/Button-Play_Game.png", 10, 120);
    firstMenu->AddMenuButton("data/Button-Settings.png", NULL, 10, 220);
    firstMenu->AddQuitButton("data/Button-Quit_to_Menu.png", 10, 320);
    mainMenuTree = new MenuTree(firstMenu);

    cursor = new Sprite("data/BlackCursor.png", -256, -256, 1.0, 1.0);
    cords = new Text("X, Y");

    components.Add(mainMenuTree);
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

    *cursor->matrix.x = input.Mouse.x;
    *cursor->matrix.y = input.Mouse.y;

    //delete cords;
    //cords = new Text(String(input.Mouse.x) + ", " + String(input.Mouse.y));
    //cords->Update();
}
