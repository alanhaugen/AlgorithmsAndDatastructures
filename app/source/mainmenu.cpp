#include <core/application.h>
#include "mainmenu.h"

mainmenu::mainmenu()
{
};

void mainmenu::Init()
{
    cam = new Camera();
    bg = new Sprite("data/BackgroundImage.png", -256.0f, -256.0f, 0.5f, 0.5f);

    Menu* playMenu = new Menu(&menus);
    playMenu->AddNextSceneButton("data/Button-Play_Against_AI.png", -7, 100);
    playMenu->AddNextSceneButton("data/Button-2_Player.png", -7, 200);
    playMenu->AddQuitButton("data/Button-Back.png", -7, 400);

    Menu* graphicsMenu = new Menu(&menus);
    graphicsMenu->AddMenuButton("data/Button-Fullscreen.png", NULL, -7, 100, "fullscreen");
    graphicsMenu->AddMenuButton("data/Button-Windowed.png", NULL, -7, 200, "windowed");
    graphicsMenu->AddQuitButton("data/Button-Back.png", -7, 400);

    Menu* audioMenu = new Menu(&menus);
    audioMenu->AddQuitButton("data/Button-Back.png", -7, 400);

    Menu* settingsMenu = new Menu(&menus);
    settingsMenu->AddMenuButton("data/Button-Audio.png", audioMenu, -7, 100);
    settingsMenu->AddMenuButton("data/Button-Graphics.png", graphicsMenu, -7, 200);
    settingsMenu->AddQuitButton("data/Button-Back.png", -7, 400);

    Menu* firstMenu = new Menu(&menus);
    firstMenu->AddMenuButton("data/Button-Play_Game.png", playMenu, -7, 100);
    firstMenu->AddMenuButton("data/Button-Settings.png", settingsMenu, -7, 200);
    firstMenu->AddMenuButton("data/Button-Load_Replay.png", NULL, -7, 300);
    firstMenu->AddQuitButton("data/Button-Quit_to_Desktop.png", -7, 400);
    menus.Push(firstMenu);

    title = new Sprite("data/Title.png", -250.0f, -50.0f, 0.5f, 0.5f);
    cursor = new Sprite("data/BlackCursor.png", -256, -256, 1.0, 1.0);
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
