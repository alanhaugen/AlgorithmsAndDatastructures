#ifndef MOVE_H
#define MOVE_H

#include <core/components/component.h>
#include <core/components/command.h>

class Piece;

class Move : public Command
{
public:
    Piece* movedPiece;
    glm::vec2 newPosition;
    glm::vec2 oldPosition;

    Move(Piece* piece, glm::vec2 position);

    void Update();

    void Execute();
    void Undo();
    void Redo();
};

#endif
