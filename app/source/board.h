#ifndef board_H
#define board_H

#include <core/components/component.h>
#include <core/components/sprite.h>
#include <core/components/camera.h>

class Board : public Component
{
public:
    Sprite* background;
    Board();

    void Init();
    void Update();
    void UpdateAfterPhysics();
};

#endif
