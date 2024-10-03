#ifndef PLAYER_H
#define PLAYER_H

#include <core/components/component.h>
#include <core/components/sprite.h>
#include <core/containers/array.h>
#include "piece.h"

class Player : public Component
{
public:
    LinkedList<Piece> pieces;
    int score;
    int gold;
    bool isWhite;
    Sprite* avatar;
    bool isComputer;

    Player();
    Player(bool isWhitePlayer, bool isAIComputerPlayer);

    void Init();

    void Update();
    void UpdateAfterPhysics();
};

#endif
