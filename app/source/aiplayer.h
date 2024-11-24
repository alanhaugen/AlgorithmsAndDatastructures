#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "player.h"
#include "minimax.h"

class AIPlayer : public Player
{
private:
    const int Depth = 5;

    Minimax minimax;

public:
    AIPlayer(bool isWhite = false);
    Array<Move> GetAllPossibleMoves(Board* gameBoard);
    Move GetNextMove(Board* gameBoard, Player* opponent = nullptr);

    ITime* thinkingTimer;
};

#endif // AIPLAYER_H
