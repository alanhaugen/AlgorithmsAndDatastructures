#ifndef PIECE_H
#define PIECE_H

#include <core/components/component.h>
#include <core/components/sprite.h>
#include <core/components/text.h>
#include <core/containers/queue.h>
#include "move.h"

class Tile;

struct Capture
{
    glm::vec2 capture;
    glm::vec2 moveTo;

    Capture()
    {
    }

    Capture(glm::vec2 capture_, glm::vec2 moveTo_)
    {
        capture = capture_;
        moveTo = moveTo_;
    }
};

class Piece : public Component
{
public:
    String name;
    String description;
    int price = 0;
    int nobility = 0;
    int range = 0;
    bool isWhite = true;
    bool isCurrentlyInAnimation = false;
    Piece* transformedPiece = nullptr;

    Text* nameText = nullptr;
    Text* movementTypeText = nullptr;
    Text* movementText = nullptr;
    Text* rangeText = nullptr;
    Text* descriptionText = nullptr;
    Text* nobilityText = nullptr;
    Text* costText = nullptr;

    Text* buyText = nullptr;

    //
    Text* flavorText = nullptr;

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
          String infoBoardPath,
          int range_ = 0,
          String Type_ = "Grounded",
          bool isJumping_ = false,
          bool canReturnAfterCapture_ = false,
          bool isHydra_ = false);

    Sprite* iconWhite = nullptr;
    Sprite* iconBlack = nullptr;

    Sprite* icon = nullptr;
    Sprite* animatedForm = nullptr;
    Sprite* backgroundCard = nullptr;
    Sprite* infoBoard = nullptr;

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
    String Type;

    Array<glm::vec2> movePattern;
    Array<Capture> captureOnlyMovePattern;
    Array<glm::vec2> weightPattern;
    Array<glm::vec2> weights;

    Array<Move> PossibleMoves();
    Queue<glm::vec2> walkingPath;

    bool isJumping = false;
    bool isActive = false;
    bool canCapture = true;
    bool canReturnAfterCapture = false;
    bool isHydra = false;
    bool isJester = false;

    bool isPerpendicularOnly = false;
    bool isDiagonalOnly = false;

    void Update();
};

#endif
