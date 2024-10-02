#include <core/application.h>
#include "button.h"

Button::Button(String filePath, int x, int y, Stack<Menu*> *menuStack_)
{
    buttonImage = new Sprite(filePath, x, y, 0.5f, 0.5f);
    menuStack = menuStack_;
};

void Button::Update()
{
    buttonImage->Update();

    if (input.Mouse.Pressed)
    {
        if ((input.Mouse.x > *buttonImage->matrix.x + (526 / 4) && input.Mouse.y > *buttonImage->matrix.y + (120 / 4)) &&
            (input.Mouse.x < *buttonImage->matrix.x + (526-132) && input.Mouse.y < *buttonImage->matrix.y + (120-30)))
        {
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
};

void Button::UpdateAfterPhysics()
{
};
