#ifndef piece_H
#define piece_H

#include <core/components/component.h>

class Piece : public Component
{
public:
    Piece();

    void Update();
    void UpdateAfterPhysics();
};

#endif
