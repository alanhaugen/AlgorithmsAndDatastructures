#ifndef MENU_H
#define MENU_H

#include <core/components/component.h>
#include <core/containers/array.h>
#include <core/containers/stack.h>
#include <core/components/sprite.h>
#include "checkbox.h"

class Button;

class Menu : public Component
{
private:
    Stack<Menu*>* menuStack;
    Array<Button*> buttons;
    Array<CheckBox*> checkBoxes;

public:
    Menu(Stack<Menu*>* menuStack_);

    void AddCheckBox(String imageUnselected, String imageSelected, String text, bool* option, int x, int y);

    void AddNextSceneButton(String image, int x, int y, String type = "nextscene", int index = 0);
    void AddNextSceneButton(Sprite *image, String type = "nextscene", int index = 0);

    void AddMenuButton(String image, Menu* menu, int x, int y, String type = 0);
    void AddMenuButton(Sprite* image, Menu* menu, String type = 0);

    void AddQuitButton(String image, int x, int y);
    void AddQuitButton(Sprite *image);

    void Update();
    void UpdateAfterPhysics();
};

#endif
