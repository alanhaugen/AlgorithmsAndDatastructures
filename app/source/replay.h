#ifndef REPLAY_H
#define REPLAY_H

#include <core/x-platform/string.h>
#include "move.h"
#include <core/containers/linkedlist.h>

class Replay
{
public:
    LinkedList<Move> Moves;
    bool Draw;
    bool WinColor;
    String PlayDate;
    Replay(LinkedList<Move> Moves, bool Draw, bool WinColor, String PlayDate);
    Replay();
};

#endif // REPLAY_H
