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
    firstMenu->AddNextSceneButton("data/Button-Play_Game.png", 10, 100);
    firstMenu->AddMenuButton("data/Button-Settings.png", NULL, 10, 200);
    firstMenu->AddMenuButton("data/Button-Load_Replay.png", NULL, 10, 300);
    firstMenu->AddQuitButton("data/Button-Quit_to_Menu.png", 10, 400);
    mainMenuTree = new MenuTree(firstMenu);
    title = new Sprite("data/Title.png");

    cursor = new Sprite("data/BlackCursor.png", -256, -256, 1.0, 1.0);
    cords = new Text("X, Y");

    components.Add(mainMenuTree);
    components.Add(title);
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
