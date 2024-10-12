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
        nobilityText = new Text("Nobility: " + String(totalNobility), 20, renderer->windowHeight - 55);
        goldText = new Text("White Gold: " + String(gold), 20, renderer->windowHeight - 160);
        goldText->y = 100;

        *buttonReady->matrix.y = renderer->windowHeight - 80;
    }
    else
    {
        nobilityText = new Text("Nobility: " + String(totalNobility), 52, 20);
        goldText = new Text("Black Gold: " + String(gold), 52, 112);
        *buttonReady->matrix.y = 85;
    }

    *buttonReady->matrix.x = renderer->windowWidth - 300;
    goldText->x = 20;
}

void Player::Init()
{
    isComputer = false;
    isWhite    = false;
    isReady    = false;
    gold       = 1000;
    score      = 0;

    buttonReady = new Sprite("data/Button-Ready.png", 0.0f, 0.0f, 0.5f, 0.5f);
    goldText    = new Text("");

    activePiece = nullptr;

    totalNobility = 0;
}

void Player::UpdateNobilityText(int nobility)
{
    if (nobility == -1)
    {
        Update();
    }
    else
    {
        totalNobility = nobility;
    }

    int x = *nobilityText->matrix.x;
    int y = *nobilityText->matrix.y;

    delete nobilityText;
    nobilityText = new Text("Nobility: " + String(totalNobility), x, y);
    nobilityText->Update();
}

void Player::UpdateGoldText()
{
    int x = *goldText->matrix.x;
    int y = *goldText->matrix.y;

    delete goldText;

    if (isWhite)
    {
        goldText = new Text("White Gold: " + String(gold), x, y);
    }
    else
    {
        goldText = new Text("Black Gold: " + String(gold), x, y);
    }

    goldText->Update();
}

void Player::Update()
{
    if (piecesInHand.Empty() == false)
    {
        int x = 70;
        int y = 30;

        if (isWhite)
        {
            y = renderer->windowHeight - 100;
        }

        totalNobility = 0;

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

            totalNobility += (*piece)->nobility;

            x += 50;
            if (x > renderer->windowWidth - 100)
            {
                y += 30;
                x = 50;
            }
        }
    }

    if (isReady == false)
    {
        if (piecesInHand.Empty() == false)
        {
            buttonReady->Update();
        }

        goldText->Update();
        nobilityText->Update();
    }
}
