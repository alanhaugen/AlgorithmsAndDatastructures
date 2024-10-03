#ifndef move_H
#define move_H

#include <core/components/component.h>

class Move : public Component
{
public:
    Move();

    void Update();
    void UpdateAfterPhysics();
};

#endif
