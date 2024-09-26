#include <core/application.h>
#include "menu.h"

Menu::Menu(Stack<Menu*> *menuStack_)
{
    menuStack  = menuStack_;
    background = NULL;
}

void Menu::SetBackground(String image)
{
    background = new Sprite(image, -256, -256, 0.5, 0.5);
}

void Menu::AddNextSceneButton(String image, int x, int y)
{
    Sprite* buttonSprite = new Sprite(image, x, y, 0.5, 0.5);
    buttonSprite->tag = "nextscene";
    buttons.Add(buttonSprite);
}

void Menu::AddMenuButton(String image, Menu *menu, int x, int y)
{
    Sprite* buttonSprite = new Sprite(image, x, y, 0.5, 0.5);
    buttonSprite->tag = "menu";
    buttons.Add(buttonSprite);
}

void Menu::AddQuitButton(String image, int x, int y)
{
    Sprite* buttonSprite = new Sprite(image, x, y, 0.5, 0.5);
    buttonSprite->tag = "quit";
    buttons.Add(buttonSprite);
}

void Menu::Update()
{
    for (unsigned int i = 0; i < buttons.Size(); i++)
    {
        buttons[i]->Update();

        if (input.Mouse.Pressed)
        {
            if ((input.Mouse.x > *buttons[i]->matrix.x + (526 / 4) && input.Mouse.y > *buttons[i]->matrix.y + (120 / 4)) &&
                (input.Mouse.x < *buttons[i]->matrix.x + (526-132) && input.Mouse.y < *buttons[i]->matrix.y + (120-30)))
            {
                if (buttons[i]->tag == "nextscene")
                {
                    Application::NextScene();
                }
                if (buttons[i]->tag == "menu")
                {
                }
                if (buttons[i]->tag == "quit")
                {
                    Application::Quit();
                }
            }
        }
    }

    background->Update();
}

void Menu::UpdateAfterPhysics()
{
};
