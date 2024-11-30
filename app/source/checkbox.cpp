#include "checkbox.h"

CheckBox::CheckBox(String imageUnSelected, String imageSelected, String text, bool* option, int x, int y)
{
    selected = new Sprite(imageSelected, x, y);
    unSelected = new Sprite(imageUnSelected, x, y);

    textSprite = new Text(text, x + 250, y + 20, 2.5f, 2.5f);

    origOption = option;

    toggled = *option;
}

CheckBox::CheckBox(String text, bool *option, int x, int y)
{
    selected = new Sprite("data/CheckboxChecked.png", x, y, 0.25f, 0.25f);
    unSelected = new Sprite("data/CheckboxEmpty.png", x, y, 0.25f, 0.25f);

    textSprite = new Text(text, x + 50, y, 1.0f, 1.0f);

    origOption = option;

    toggled = *option;
}

void CheckBox::Update()
{
    if (toggled)
    {
        selected->Update();
    }
    else
    {
        unSelected->Update();
    }

    if (selected->IsPressed() || unSelected->IsPressed())
    {
        toggled = !toggled;
        *origOption = toggled;
    }

    textSprite->Update();
}
