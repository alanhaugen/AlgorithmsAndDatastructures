#ifndef MENU_H
#define MENU_H

#include <core/components/component.h>
#include <core/containers/array.h>
#include <core/containers/stack.h>
#include <core/components/sprite.h>

class Button;

class Menu : public Component
{
private:
    Stack<Menu*>* menuStack;
    Array<Button*> buttons;

public:
    Menu(Stack<Menu*>* menuStack_);
    void AddNextSceneButton(String image, int x, int y, String type = "nextscene", int index = 0);
    void AddMenuButton(String image, Menu* menu, int x, int y, String type = 0);
    void AddMenuButton(Sprite* image, Menu* menu, String type = 0);
    void AddQuitButton(String image, int x, int y);

    void Update();
};

#endif
