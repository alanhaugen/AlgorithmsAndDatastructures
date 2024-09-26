#ifndef mainmenu_H
#define mainmenu_H

#include <core/x-platform/scene.h>
#include <core/components/sprite.h>
#include <core/components/camera.h>
#include <core/components/text.h>
#include "menutree.h"

class mainmenu : public IScene
{
public:
    Sprite* title;
    MenuTree* mainMenuTree;
    Sprite* cursor;
    Camera* cam;
    Text* cords;
    mainmenu();

    void Init();
    void Update();
};

#endif
