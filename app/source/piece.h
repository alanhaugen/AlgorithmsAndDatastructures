#ifndef PIECE_H
#define PIECE_H

#include <core/components/component.h>
#include <core/components/sprite.h>
#include <core/components/text.h>
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

    Text* nameText = nullptr;
    Text* movementTypeText = nullptr;
    Text* movementText = nullptr;
    Text* rangeText = nullptr;
    Text* descriptionText = nullptr;
    Text* nobilityText = nullptr;
    Text* costText = nullptr;

    Text* buyText = nullptr;

    bool invinsible = false;

    LinkedList<Piece*>::LinkedNode* listNode = nullptr;

public:
    Piece();
    Piece(String name_,
          String iconWhitePath,
          String iconBlackPath,
          String description_,
          int price_,
          int nobility,
          int range = 0,
          bool isJumping_ = false,
          bool canReturnAfterCapture_ = false,
          bool isHydra_ = false);

    Sprite* iconWhite = nullptr;
    Sprite* iconBlack = nullptr;

    Sprite* icon = nullptr;
    Sprite* backgroundCard = nullptr;

    Tile* currentTile = nullptr;
    Sprite* idleSprite = nullptr;
    Sprite* walkingSprite = nullptr;
    Sprite* attackSprite = nullptr;
    Sprite* deathSprite = nullptr;

    Sprite* tileBorderBlue = nullptr;
    Sprite* tileBorderGold = nullptr;

    String footstepSound;
    String attackSound;
    String dieSound;

    Array<glm::vec2> movePattern;
    Array<glm::vec2> captureOnlyMovePattern;
    Array<glm::vec2> weightPattern;
    Array<glm::vec2> weights;

    Array<Move> PossibleMoves();
    Queue<glm::vec2> walkingPath;

    bool isJumping = false;
    bool isActive = false;
    bool canCapture = true;
    bool canReturnAfterCapture = false;
    bool isHydra = false;

    void Update();
};

#endif
