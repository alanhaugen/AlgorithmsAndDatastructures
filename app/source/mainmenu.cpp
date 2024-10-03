#include <core/application.h>
#include "mainmenu.h"

mainmenu::mainmenu()
{
};

void mainmenu::Init()
{
    cam = new Camera();
    bg = new Sprite("data/BackgroundImage.png", 0.0f, 0.0f, 0.5f, 0.5f);

    Menu* playMenu = new Menu(&menus);
    playMenu->AddNextSceneButton("data/Button-Play_Against_AI.png", 125, 130);
    playMenu->AddNextSceneButton("data/Button-2_Player.png", 125, 230);
    playMenu->AddQuitButton("data/Button-Back.png", 125, 430);

    Menu* graphicsMenu = new Menu(&menus);
    graphicsMenu->AddMenuButton("data/Button-Fullscreen.png", NULL, 125, 130, "fullscreen");
    graphicsMenu->AddMenuButton("data/Button-Windowed.png", NULL, 125, 230, "windowed");
    graphicsMenu->AddQuitButton("data/Button-Back.png", 125, 430);

    Menu* audioMenu = new Menu(&menus);
    audioMenu->AddQuitButton("data/Button-Back.png", 125, 430);

    Menu* settingsMenu = new Menu(&menus);
    settingsMenu->AddMenuButton("data/Button-Audio.png", audioMenu, 125, 130);
    settingsMenu->AddMenuButton("data/Button-Graphics.png", graphicsMenu, 125, 230);
    settingsMenu->AddQuitButton("data/Button-Back.png", 125, 430);

    Menu* firstMenu = new Menu(&menus);
    firstMenu->AddMenuButton("data/Button-Play_Game.png", playMenu, 125, 130);
    firstMenu->AddMenuButton("data/Button-Settings.png", settingsMenu, 125, 230);
    firstMenu->AddMenuButton("data/Button-Load_Replay.png", NULL, 125, 330);
    firstMenu->AddQuitButton("data/Button-Quit_to_Desktop.png", 125, 430);
    menus.Push(firstMenu);

    title = new Sprite("data/Title.png", 5.0f, 15.0f, 0.5f, 0.5f);
    cursor = new Sprite("data/BlackCursor.png", 0, 0, 1.0, 1.0);
    cords = new Text("X, Y");

    components.Add(bg);
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

    menus.Top()->Update();

    *cursor->matrix.x = input.Mouse.x;
    *cursor->matrix.y = input.Mouse.y;

    //delete cords;
    //cords = new Text(String(input.Mouse.x) + ", " + String(input.Mouse.y));
    //cords->Update();
}
