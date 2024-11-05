#include "menu.h"
#include "button.h"

Menu::Menu(Stack<Menu*> *menuStack_)
{
    menuStack  = menuStack_;
}

void Menu::AddNextSceneButton(String image, int x, int y, String type, int index)
{
    Button* button = new Button(image, x, y, menuStack);
    button->tag = type;
    buttons.Add(button);
    button->index = index;
}

void Menu::AddMenuButton(String image, Menu *menu, int x, int y, String type)
{
    Button* button = new Button(image, x, y, menuStack);
    button->tag = type;
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
