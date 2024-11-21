#include <core/application.h>
#include "mainmenu.h"
#include "replaynew.h"

extern LinkedList<ReplayNew> replays;

Mainmenu::Mainmenu()
{
//#ifdef WIN32
//    FRAME_TIME_MS = 1000.0f / 140.0f;
//#endif
}

void Mainmenu::Init()
{
    cam = new Camera();
    bg  = new Sprite("data/BackgroundImage.png", 0.0f, 0.0f, 1.78f, 1.78f);
    menus.Clear();

    Menu* playMenu = new Menu(&menus);
    playMenu->AddNextSceneButton("data/Button-Play_Against_AI.png", renderer->windowWidth / 2 - 200, 130 * (1.75), "vsAI");
    playMenu->AddNextSceneButton("data/Button-2_Player.png", renderer->windowWidth / 2 - 200, 210 * (1.75), "vsPlayer");
    playMenu->AddNextSceneButton("data/Button-Auto_Battler.png", renderer->windowWidth / 2 - 200, 290 * (1.75), "AIvsAI");
    playMenu->AddQuitButton("data/Button-Back.png", renderer->windowWidth / 2 - 200, 370 * (1.75));

    Menu* graphicsMenu = new Menu(&menus);
    graphicsMenu->AddMenuButton("data/Button-Fullscreen.png", NULL, renderer->windowWidth / 2 - 200, 130 * (1.75), "fullscreen");
    graphicsMenu->AddMenuButton("data/Button-Windowed.png", NULL, renderer->windowWidth / 2 - 200, 210 * (1.75), "windowed");
    graphicsMenu->AddQuitButton("data/Button-Back.png", renderer->windowWidth / 2 - 200, 370 * (1.75));

    Menu* audioMenu = new Menu(&menus);
    audioMenu->AddQuitButton("data/Button-Back.png", renderer->windowWidth / 2 - 200, 370 * (1.75));

    Menu* settingsMenu = new Menu(&menus);
    settingsMenu->AddMenuButton("data/Button-Audio.png", audioMenu, renderer->windowWidth / 2 - 200, 130 * (1.75));
    settingsMenu->AddMenuButton("data/Button-Graphics.png", graphicsMenu, renderer->windowWidth / 2 - 200, 210 * (1.75));
    settingsMenu->AddQuitButton("data/Button-Back.png", renderer->windowWidth / 2 - 200, 370 * (1.75));

    replaysMenu = new Menu(&menus);
    replayBG = new Sprite("data/ReplayMenuBackground.png", renderer->windowWidth / 2 - 200, 80, 0.75f, 0.75f);
    replaysMenu->AddQuitButton("data/Button-Back.png", renderer->windowWidth / 2 - 200, 370 * (1.75));

    //replays.Append(ReplayNew()); //for test, skal fjernes

    LinkedList<ReplayNew>::Iterator replayI = replays.Begin();
    for(int i = 0; replayI != NULL; ++replayI)
    {
        if(replayI->Draw == true)
        {
            replaysMenu->AddNextSceneButton("data/DrawReplayButton.png", renderer->windowWidth/2 - 501*0.75*0.5 - 2, 90 + i*45, "Replay", i);
        } else
        if(replayI->WinColor == true)
        {
            replaysMenu->AddNextSceneButton("data/WhitePlayerReplayButton.png", renderer->windowWidth/2 - 501*0.75*0.5 - 2, 90 + i*45, "Replay", i);
        } else
        {
            replaysMenu->AddNextSceneButton("data/DarkPlayerReplayButton.png",  renderer->windowWidth/2 - 501*0.75*0.5 - 2, 90+i*45, "Replay", i);
        }

        i++;
    }

    Menu* firstMenu = new Menu(&menus);
    firstMenu->AddMenuButton("data/Button-Play_Game.png", playMenu, renderer->windowWidth / 2 - 200, 130 * (1.75));
    firstMenu->AddMenuButton("data/Button-Settings.png", settingsMenu, renderer->windowWidth / 2 - 200, 210 * (1.75));
    firstMenu->AddMenuButton("data/Button-Load_Replay.png", replaysMenu, renderer->windowWidth / 2 - 200, 290 * (1.75));
    firstMenu->AddQuitButton("data/Button-Quit_to_Desktop.png", renderer->windowWidth / 2 - 200, 370 * (1.75));


    menus.Push(firstMenu);

    title = new Sprite("data/Title.png", 0, 5.0f * (1.75), 1.00f, 1.00f);
    *title->matrix.x = (renderer->windowWidth / 2) - (title->width / 2);
    cursor = new Cursor();
    cords = new Text("X,Y");

    components.Add(bg);
    components.Add(title);
    components.Add(cam);
    components.Add(cursor);
}

void Mainmenu::Update()
{
    menus.Top()->Update();
    if(menus.Top() == replaysMenu)
    {
        replayBG->Update();
        title->Hide();
    } else
    {
        title->Show();
    }
    //delete cords;
    //cords = new Text(String(input.Mouse.x) + ", " + String(input.Mouse.y));
    //cords->Update();
}
