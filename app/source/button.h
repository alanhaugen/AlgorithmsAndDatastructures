#ifndef BUTTON_H
#define BUTTON_H

#include <core/components/component.h>
#include <core/components/sprite.h>
#include "menu.h"

class Button : public Component
{
private:
    Sprite* buttonImage = NULL;
    Stack<Menu*>* menuStack = NULL;

public:
    Menu* gotoMenu = NULL;
    Button(String filePath, int x, int y, Stack<Menu *> *menuStack_);

    void Update();
};

#endif
