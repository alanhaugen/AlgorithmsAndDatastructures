#ifndef MENU_H
#define MENU_H

#include <core/components/component.h>
#include <core/containers/array.h>
#include <core/components/sprite.h>

class Menu : public Component
{
private:
    Sprite* background;
    Array<Sprite*> buttons;

public:
    Menu();
    void SetBackground(String image);
    void AddNextSceneButton(String image, int x, int y);
    void AddMenuButton(String image, Menu* menu, int x, int y);
    void AddQuitButton(String image, int x, int y);

    void Update();
    void UpdateAfterPhysics();
};

#endif
