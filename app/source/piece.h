#ifndef piece_H
#define piece_H

#include <core/components/component.h>
#include <core/components/sprite.h>
#include <core/containers/queue.h>
#include "move.h"

class Piece : public Component
{
public:
    String name;
    Sprite* icon;
    String description;
    int price;
    int nobility;
    int range;
    Sprite* idleSprite;
    Sprite* walkingSprite;
    Sprite* attackSprite;
    Sprite* deathSprite;
    String footstepSound;
    String attackSound;
    String dieSound;
    bool isFlying;
    bool isActive;
    Array<glm::vec2> movePattern;
    Array<glm::vec2> weights;

    Piece();

    void Update();
    void UpdateAfterPhysics();

    Array<Move> PossibleMoves();
    Queue<glm::vec2> walkingPath;
};

#endif
