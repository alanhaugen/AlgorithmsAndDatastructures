#include <core/application.h>
#include "button.h"
#include "main.h"
#include "replaynew.h"

extern bool isTwoPlayer;
extern bool vsAI;
extern LinkedList<Move> replay;
extern LinkedList<ReplayNew> replays;

Button::Button(String filePath, int x, int y, Stack<Menu*> *menuStack_)
{
    buttonImage = new Sprite(filePath, x, y, 0.75f, 0.75f);
    menuStack = menuStack_;
}

Button::Button(Sprite *image, Stack<Menu *> *menuStack_)
{
    buttonImage = image;
    menuStack = menuStack_;
}

void Button::Update()
{
    buttonImage->Update();

    if (buttonImage->IsPressed())
    {
        if (tag == "Replay")
        {
            LinkedList<ReplayNew>::Iterator Replay_ = replays.Begin();

            for(int i = 0; Replay_ != NULL; ++Replay_)
            {
                if(i == index)
                {
                    replay = *(*Replay_).Moves;
                    break;
                }
                i++;
            }
            Application::LoadScene(Scenes::Replay);
        }
        if (tag == "vsAI")
        {
            isTwoPlayer = true;
            vsAI        = true;
            Application::NextScene();
        }
        if (tag == "AIvsAI")
        {
            isTwoPlayer = false;
            vsAI        = true;
            Application::NextScene();
        }
        if (tag == "vsPlayer")
        {
            isTwoPlayer = true;
            vsAI        = false;
            Application::NextScene();
        }
        if (tag == "nextscene")
        {
            Application::NextScene();
        }
        if (tag == "fullscreen")
        {
            Locator::renderer->Fullscreen();
        }
        if (tag == "windowed")
        {
            Locator::renderer->Windowed();
        }
        if (gotoMenu != NULL)
        {
            menuStack->Push(gotoMenu);
        }
        if (tag == "quit")
        {
            if (menuStack->Size() == 1)
            {
                Application::Quit();
            }
            else
            {
                menuStack->Pop();
            }
        }
        if (tag == "Replay")
        {
            Application::NextScene();
        }
    }
}
