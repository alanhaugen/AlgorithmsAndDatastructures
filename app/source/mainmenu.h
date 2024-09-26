#ifndef mainmenu_H
#define mainmenu_H

#include <core/x-platform/scene.h>
#include <core/components/sprite.h>
#include <core/components/camera.h>
#include <core/containers/stack.h>
#include <core/components/text.h>
#include "menu.h"

class mainmenu : public IScene
{
public:
    Stack<Menu*> menus;
    Sprite* title;
    Sprite* bg;
    Sprite* cursor;
    Camera* cam;
    Text* cords;
    mainmenu();

    void Init();
    void Update();
};

#endif
