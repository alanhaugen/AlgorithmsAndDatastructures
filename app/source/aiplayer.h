#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "player.h"
#include "minimax.h"

class AIPlayer : public Player
{
private:
    const int Depth = 2;

    ITime* thinkingTimer;
    Minimax minimax;

public:
    AIPlayer(bool isWhite = false);
    Array<Move> GetAllPossibleMoves(Board* gameBoard);
    Move GetNextMove(Board* gameBoard, Player* opponent = nullptr);
};

#endif // AIPLAYER_H
