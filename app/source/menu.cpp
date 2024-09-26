#include "menu.h"
#include "button.h"

Menu::Menu(Stack<Menu*> *menuStack_)
{
    menuStack  = menuStack_;
    background = NULL;

    tempButtonMenu = NULL;
}

void Menu::AddNextSceneButton(String image, int x, int y)
{
    Button* button = new Button(image, x, y, menuStack);
    button->tag = "nextscene";
    buttons.Add(button);
}

void Menu::AddMenuButton(String image, Menu *menu, int x, int y)
{
    Button* button = new Button(image, x, y, menuStack);
    button->tag = "menu";
    button->gotoMenu = menu;
    buttons.Add(button);
}

void Menu::AddQuitButton(String image, int x, int y)
{
    Button* button = new Button(image, x, y, menuStack);
    button->tag = "quit";
    buttons.Add(button);
}

void Menu::Update()
{
    for (unsigned int i = 0; i < buttons.Size(); i++)
    {
        buttons[i]->Update();
    }
}

void Menu::UpdateAfterPhysics()
{
};
