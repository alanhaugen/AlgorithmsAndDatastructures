#ifndef MOVE_H
#define MOVE_H

#include <core/components/component.h>

class Piece;

class Move : public Component
{
public:
    Piece* MovedPiece;
    glm::vec2 position;

    Move();

    void Update();
    void UpdateAfterPhysics();
};

#endif
