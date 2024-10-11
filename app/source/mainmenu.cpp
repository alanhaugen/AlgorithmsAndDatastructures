#include <core/application.h>
#include "mainmenu.h"

Mainmenu::Mainmenu()
{
};

void Mainmenu::Init()
{
    cam = new Camera();
    bg  = new Sprite("data/BackgroundImage.png", 0.0f, 0.0f, 0.75f, 0.75f);
    menus.Clear();

    Menu* playMenu = new Menu(&menus);
    playMenu->AddNextSceneButton("data/Button-Play_Against_AI.png", 190, 130 * (1.75));
    playMenu->AddNextSceneButton("data/Button-2_Player.png", 190, 210 * (1.75));
    playMenu->AddQuitButton("data/Button-Back.png", 190, 370 * (1.75));

    Menu* graphicsMenu = new Menu(&menus);
    graphicsMenu->AddMenuButton("data/Button-Fullscreen.png", NULL, 190, 130 * (1.75), "fullscreen");
    graphicsMenu->AddMenuButton("data/Button-Windowed.png", NULL, 190, 210 * (1.75), "windowed");
    graphicsMenu->AddQuitButton("data/Button-Back.png", 190, 370 * (1.75));

    Menu* audioMenu = new Menu(&menus);
    audioMenu->AddQuitButton("data/Button-Back.png", 190, 370 * (1.75));

    Menu* settingsMenu = new Menu(&menus);
    settingsMenu->AddMenuButton("data/Button-Audio.png", audioMenu, 190, 130 * (1.75));
    settingsMenu->AddMenuButton("data/Button-Graphics.png", graphicsMenu, 190, 210 * (1.75));
    settingsMenu->AddQuitButton("data/Button-Back.png", 190, 370 * (1.75));

    Menu* firstMenu = new Menu(&menus);
    firstMenu->AddMenuButton("data/Button-Play_Game.png", playMenu, 190, 130 * (1.75));
    firstMenu->AddMenuButton("data/Button-Settings.png", settingsMenu, 190, 210 * (1.75));
    firstMenu->AddMenuButton("data/Button-Load_Replay.png", NULL, 190, 290 * (1.75));
    firstMenu->AddQuitButton("data/Button-Quit_to_Desktop.png", 190, 370 * (1.75));
    menus.Push(firstMenu);

    title = new Sprite("data/Title.png", 5.0f * (1.75), 15.0f * (1.75), 0.75f, 0.75f);
    cursor = new Cursor();
    cords = new Text("X, Y");

    components.Add(bg);
    components.Add(title);
    components.Add(cam);
    components.Add(cursor);
};

void Mainmenu::Update()
{
    menus.Top()->Update();

    //delete cords;
    //cords = new Text(String(input.Mouse.x) + ", " + String(input.Mouse.y));
    //cords->Update();
}
