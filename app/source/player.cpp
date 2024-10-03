#include "player.h"

Player::Player()
{
    Init();
}

Player::Player(bool isWhitePlayer, bool isAIComputerPlayer)
{
    Init();

    isWhite    = isWhitePlayer;
    isComputer = isAIComputerPlayer;
}

void Player::Init()
{
    isComputer = false;
    isWhite    = false;
    gold       = 1000;
    score      = 0;
}

void Player::Update()
{
}

void Player::UpdateAfterPhysics()
{
}

