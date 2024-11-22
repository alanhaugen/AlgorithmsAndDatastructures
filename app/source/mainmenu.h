#ifndef MAINMENU_H
#define MAINMENU_H

#include <core/x-platform/scene.h>
#include <core/components/sprite.h>
#include <core/components/camera.h>
#include <core/containers/stack.h>
#include <core/components/text.h>
#include "menu.h"
#include "cursor.h"

class Mainmenu : public IScene
{
public:
    Stack<Menu*> menus;
    Menu* replaysMenu;
    Sprite* title;
    Sprite* bg;
    Sprite* rulebook;
    Sprite* replayBG;
    Sprite* testPopUp;
    Cursor* cursor;
    Camera* cam;
    Text* cords;
    Mainmenu();

    void Init();
    void Update();
};

#endif
