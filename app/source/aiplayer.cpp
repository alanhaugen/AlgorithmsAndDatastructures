#include <core/application.h>
#include "aiplayer.h"

AIPlayer::AIPlayer(bool isWhite)
{
    thinkingTimer = Application::GetTime("wait time");
    Init(isWhite);
}

Move AIPlayer::GetNextMove(Board *gameBoard, Player* opponent)
{
    // Wait about a second before making a move
    if (thinkingTimer->TimeSinceStarted() < 900.0f)
    {
        return Move();
    }

    thinkingTimer->Reset();

    // Get best move
    //return minimax.FindBestMove(this, opponent, gameBoard, Depth);

    // Do a random move
    Player::GetAllPossibleMoves(gameBoard);
    return moves[random.RandomRange(0, moves.Size())];
}
