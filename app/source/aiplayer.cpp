#include <core/application.h>
#include "aiplayer.h"

AIPlayer::AIPlayer(bool isWhite)
{
    thinkingTimer = Application::GetTime("wait time");
    Init(isWhite);
}

Move AIPlayer::GetNextMove(Board *gameBoard)
{
    // Wait about a second before making a move
    if (thinkingTimer->TimeSinceStarted() < 900.0f)
    {
        return Move();
    }

    thinkingTimer->Reset();

    return Move();
}
