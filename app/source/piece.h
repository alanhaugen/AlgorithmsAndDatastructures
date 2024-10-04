#ifndef PIECE_H
#define PIECE_H

#include <core/components/component.h>
#include <core/components/sprite.h>
#include <core/containers/queue.h>
#include "move.h"

class Tile;

class Piece : public Component
{
public:
    String name;
    String description;
    int price;
    int nobility;
    int range;
    String footstepSound;
    String attackSound;
    String dieSound;

public:
    Piece();
    Piece(String name_,
          String iconPath,
          String description_,
          int price_,
          int range_);

    void Init();

    Sprite* icon;
    Tile* currentTile;
    Sprite* idleSprite;
    Sprite* walkingSprite;
    Sprite* attackSprite;
    Sprite* deathSprite;

    Array<glm::vec2> movePattern;
    Array<glm::vec2> weights;

    void Update();
    void UpdateAfterPhysics();

    Array<Move> PossibleMoves();
    Queue<glm::vec2> walkingPath;

    bool isFlying;
    bool isActive;
};

#endif
