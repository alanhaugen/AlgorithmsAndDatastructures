#include <core/application.h>
#include "button.h"

extern bool isTwoPlayer;

Button::Button(String filePath, int x, int y, Stack<Menu*> *menuStack_)
{
    buttonImage = new Sprite(filePath, x, y, 0.75f, 0.75f);
    menuStack = menuStack_;
}

void Button::Update()
{
    buttonImage->Update();

    if (buttonImage->IsPressed())
    {
        if (tag == "vsAI")
        {
            isTwoPlayer = false;
            Application::NextScene();
        }
        if (tag == "vsPlayer")
        {
            isTwoPlayer = true;
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
    }
}
