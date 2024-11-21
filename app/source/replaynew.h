#ifndef REPLAYNEW_H
#define REPLAYNEW_H
#include "move.h"
#include "board.h"
#include <core/containers/linkedlist.h>

class ReplayNew
{
public:
    LinkedList<Move>* Moves;
    bool Draw;
    bool WinColor;
    String PlayDate;
    Board* gameBoard;
    ReplayNew();
    ReplayNew(LinkedList<Move>* Moves_, bool Draw_, bool WinColor_, String PlayDate_);
};

#endif // REPLAYNEW_H
