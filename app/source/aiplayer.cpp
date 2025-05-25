#include <core/application.h>
#include "aiplayer.h"

AIPlayer::AIPlayer(bool isWhite)
{
    thinkingTimer = Application::GetTime("wait time");
    Init(isWhite);
}

// In order to choose the best possible move,
// we have to consider the game from our opponents perspective
Move AIPlayer::GetNextMove(Board *gameBoard, Player* opponent, bool isFirstMove)
{
    // Wait about a second before making a move
    if (thinkingTimer->TimeSinceStarted() < 900.0f)
    {
        return Move();
    }

    AIPlayer* aiPlayer = dynamic_cast<AIPlayer*>(opponent);

    // Reset opponent's AI thinking timer if the player is AI
    if (aiPlayer != nullptr)
    {
        aiPlayer->thinkingTimer->Reset();
    }

    // Get best move
    //return minimax.FindBestMove(this, opponent, gameBoard, Depth, isFirstMove);

    // Do a random move
    //Player::GetAllPossibleMoves(gameBoard);
    //return moves[random.RandomRange(0, moves.Size())];

    // Do a random move or capture
    Player::GetAllPossibleMoves(gameBoard);

    for (unsigned int i = 0; i < moves.Size(); i++)
    {
        if (moves[i].captureTile1 != nullptr)
        {
            return moves[i];
        }
    }

    return moves[random.RandomRange(0, moves.Size())];
}
