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
    int price = 0;
    int nobility = 0;
    int range = 0;
    bool isWhite = true;

    LinkedList<Piece*>::LinkedNode* listNode = nullptr;

public:
    Piece();
    Piece(String name_,
          String iconWhitePath,
          String iconBlackPath,
          String description_,
          int price_,
          int nobility);

    Sprite* iconWhite = nullptr;
    Sprite* iconBlack = nullptr;

    Sprite* icon = nullptr;

    Tile* currentTile = nullptr;
    Sprite* idleSprite = nullptr;
    Sprite* walkingSprite = nullptr;
    Sprite* attackSprite = nullptr;
    Sprite* deathSprite = nullptr;

    String footstepSound;
    String attackSound;
    String dieSound;

    Array<glm::vec2> movePattern;
    Array<glm::vec2> weights;

    Array<Move> PossibleMoves();
    Queue<glm::vec2> walkingPath;

    bool isFlying = false;
    bool isActive = false;

    void Update();
};

#endif
