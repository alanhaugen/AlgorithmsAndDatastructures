#include "player.h"

Player::Player(bool isWhitePlayer, bool isAIComputerPlayer)
{
    isComputer = false;
    isWhite    = isWhitePlayer;
    isComputer = isAIComputerPlayer;
    gold       = 1000;
    score      = 0;
}

void Player::Update()
{
}

void Player::UpdateAfterPhysics()
{
}

