#include "replaynew.h"

ReplayNew::ReplayNew()
{
}

ReplayNew::ReplayNew(LinkedList<Move>* Moves_, bool Draw_, bool WinColor_, String PlayDate_)
{
    Moves = new LinkedList<Move>;
    LinkedList<Move>::Iterator moves = Moves_->Begin();

    for(; moves != NULL; ++moves)
    {
        Moves->Append((*moves));
    }

    Draw = Draw_;
    WinColor = WinColor_;
    PlayDate = PlayDate_;
}
