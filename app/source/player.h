#ifndef PLAYER_H
#define PLAYER_H

#include <core/components/component.h>
#include <core/components/sprite.h>
#include <core/containers/array.h>
#include "piece.h"

class Player : public Component
{
public:
    Array<Piece> pieces;
    int score;
    int gold;
    bool isWhite;
    Sprite* avatar;
    bool isComputer;

    Player(bool isWhitePlayer, bool isAIComputerPlayer);

    void Update();
    void UpdateAfterPhysics();
};

#endif
