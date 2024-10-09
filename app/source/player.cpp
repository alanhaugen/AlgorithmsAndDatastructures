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

    delete goldText;

    if (isWhite)
    {
        nobilityText = new Text("NOBILITY: " + String(totalNobility), 20, 410, 0.4, 0.4);
        goldText = new Text("WHITE GOLD: " + String(gold), 20, 400, 0.4, 0.4);
        goldText->y = 100;

        *buttonReady->matrix.x = 350;
        *buttonReady->matrix.y = 400;
    }
    else
    {
        nobilityText = new Text("NOBILITY: " + String(totalNobility), 40, 100, 0.4, 0.4);
        goldText = new Text("BLACK GOLD: " + String(gold), 40, 90, 0.4, 0.4);
        *buttonReady->matrix.x = 350;
        *buttonReady->matrix.y = 90;
    }

    goldText->x = 20;
}

void Player::Init()
{
    isComputer = false;
    isWhite    = false;
    isReady    = false;
    gold       = 1000;
    score      = 0;

    buttonReady = new Sprite("data/Button-Ready.png", 0.0f, 0.0f, 0.25f, 0.25f);
    goldText    = new Text("");

    activePiece = nullptr;

    totalNobility = 0;
}

void Player::Update()
{
    if (piecesInHand.Empty() == false)
    {
        int x = 50;
        int y = 20;

        if (isWhite)
        {
            y = 420;
        }

        LinkedList<Piece*>::Iterator piece = piecesInHand.Begin();

        for (; piece != piecesInHand.End(); ++piece)
        {
            (*piece)->listNode = piece.curNode;
            *(*piece)->icon->matrix.x = x;
            *(*piece)->icon->matrix.y = y;
            (*piece)->Update();

            if ((*piece)->icon->IsPressed())
            {
                activePiece = (*piece);
            }

            x += 50;
            if (x > 400)
            {
                y += 30;
                x = 50;
            }
        }
    }

    if (isReady == false)
    {
        buttonReady->Update();
        goldText->Update();
        nobilityText->Update();
    }
}
