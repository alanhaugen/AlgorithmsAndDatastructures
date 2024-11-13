#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "player.h"

class AIPlayer : public Player
{
private:
    ITime* thinkingTimer;

public:
    AIPlayer(bool isWhite = false);
    Array<Move> GetAllPossibleMoves(Board* gameBoard);
    Move GetNextMove(Board* gameBoard);
};

#endif // AIPLAYER_H
