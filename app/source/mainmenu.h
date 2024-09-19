#ifndef mainmenu_H
#define mainmenu_H

#include <core/x-platform/scene.h>
#include <core/components/sprite.h>
#include <core/components/camera.h>

class mainmenu : public IScene
{
public:
    Sprite* image;
    Camera* cam;
    mainmenu();

    void Init();
    void Update();
};

#endif
