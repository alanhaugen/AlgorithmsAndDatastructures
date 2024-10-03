#ifndef board_H
#define board_H

#include <core/x-platform/scene.h>
#include <core/components/sprite.h>
#include <core/components/camera.h>

class Board : public IScene
{
public:
    Sprite* image;
    Board();

    void Init();
    void Update();
};

#endif
