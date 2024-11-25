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

    input.Mouse.Pressed = false;

    rulebook = new Sprite("data/SPRITE-RulebookPNG.png", 20, renderer->windowHeight -20, 3, 3, glm::vec2(0, 1));

    ruleMenu = new Menu(&menus);
    ruleMenu->AddQuitButton(
        new Sprite("data/Button-Back.png", renderer->windowWidth / 2, renderer->windowHeight - 30, 0.7, 0.7, glm::vec2(0.5, 1))
        );
    rules = new Rulebook(true);

    Menu* playMenu = new Menu(&menus);
    playMenu->AddNextSceneButton("data/Button-Play_Against_AI.png", renderer->windowWidth / 2 - 200, 130 * (1.75), "vsAI");
    playMenu->AddNextSceneButton("data/Button-2_Player.png", renderer->windowWidth / 2 - 200, 210 * (1.75), "vsPlayer");
    playMenu->AddNextSceneButton("data/Button-Auto_Battler.png", renderer->windowWidth / 2 - 200, 290 * (1.75), "AIvsAI");
    playMenu->AddQuitButton("data/Button-Back.png", renderer->windowWidth / 2 - 200, 370 * (1.75));
    playMenu->AddMenuButton(
        new Sprite("data/SPRITE-RulebookPNG.png", 20, renderer->windowHeight -20, 3, 3, glm::vec2(0, 1)),
        ruleMenu);




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
    replayBG = new Sprite("data/ReplayMenuBackground.png", renderer->windowWidth / 2, 75, 1, 1, glm::vec2(0.5,0));
    replaysMenu->AddQuitButton("data/Button-Back.png", renderer->windowWidth / 2 - 200, 370 * (1.75));

    //replays.Append(ReplayNew()); //for test, skal fjernes

    LinkedList<ReplayNew>::Iterator replayI = replays.Begin();
    for(int i = 0; replayI != NULL; ++replayI)
    {
        if(replayI->Draw == true)
        {
            replaysMenu->AddNextSceneButton(new Sprite("data/DrawReplayButton.png", renderer->windowWidth/2, 125 + i*75, 1, 1, glm::vec2(0.5, 0.5)), "Replay", i);
        } else
        if(replayI->WinColor == true)
        {
            replaysMenu->AddNextSceneButton(new Sprite("data/WhitePlayerReplayButton.png", renderer->windowWidth/2, 125 + i*75, 1, 1, glm::vec2(0.5, 0.5)), "Replay", i);
        } else
        {
            replaysMenu->AddNextSceneButton(new Sprite("data/DarkPlayerReplayButton.png", renderer->windowWidth/2, 125 + i*75, 1, 1, glm::vec2(0.5, 0.5)), "Replay", i);
        }
        replayI->PlayDate.TrimRight();
        Text* text = new Text(replayI->PlayDate, renderer->windowWidth/2 + replayBG->width * replayBG->scaleX/2 - 15, 125 + i*75, 1, 1, glm::vec2(1, 0.5));
        Timestamps.Append(text);
        i++;
    }

    Menu* firstMenu = new Menu(&menus);
    firstMenu->AddMenuButton("data/Button-Play_Game.png", playMenu, renderer->windowWidth / 2 - 200, 130 * (1.75));
    firstMenu->AddMenuButton("data/Button-Settings.png", settingsMenu, renderer->windowWidth / 2 - 200, 210 * (1.75));
    firstMenu->AddMenuButton("data/Button-Load_Replay.png", replaysMenu, renderer->windowWidth / 2 - 200, 290 * (1.75));
    firstMenu->AddQuitButton("data/Button-Quit_to_Desktop.png", renderer->windowWidth / 2 - 200, 370 * (1.75));
    firstMenu->AddMenuButton(
        new Sprite("data/SPRITE-RulebookPNG.png", 20, renderer->windowHeight -20, 3, 3, glm::vec2(0, 1)),
        ruleMenu);


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
    if(menus.Top() == ruleMenu)
    {
        title->Hide();
        rules->Update();
    }
    else if(menus.Top() == replaysMenu)
    {
        replayBG->Update();
        title->Hide();
        LinkedList<Text*>::Iterator PlayDateI = Timestamps.Begin();
        for(; PlayDateI != NULL; ++PlayDateI)
        {
            (*PlayDateI)->Update();
        }
    } else
    {
        title->Show();
    }


    if(menus.count > 1 && input.Pressed(input.Key.ESCAPE) == true)
    {
        menus.Pop();
    }

    //delete cords;
    //cords = new Text(String(input.Mouse.x) + ", " + String(input.Mouse.y));
    //cords->Update();
}
