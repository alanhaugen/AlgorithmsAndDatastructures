#ifndef PLAYER_H
#define PLAYER_H

#include <core/components/component.h>
#include <core/components/sprite.h>
#include <core/containers/array.h>
#include <core/components/text.h>
#include "piece.h"

class Player : public Component
{
public:
    LinkedList<Piece*> piecesInHand;
    int score;
    int gold;
    bool isWhite;
    Sprite* avatar;
    Sprite* buttonReady;
    bool isComputer;

    bool isReady;

    int totalNobility;

    Text* goldText;
    Text* nobilityText;

    Piece* activePiece;

    Player();
    Player(bool isWhitePlayer, bool isAIComputerPlayer);

    void Init();

    void Update();
};

#endif
