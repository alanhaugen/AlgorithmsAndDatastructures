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
    Sprite* background;
    Array<Button*> buttons;

    Menu* tempButtonMenu;

public:
    Menu(Stack<Menu*>* menuStack_);
    void AddNextSceneButton(String image, int x, int y);
    void AddMenuButton(String image, Menu* menu, int x, int y);
    void AddQuitButton(String image, int x, int y);

    void Update();
    void UpdateAfterPhysics();
};

#endif
