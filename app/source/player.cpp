#include "player.h"

Player::Player()
{
    Init();
}

Player::Player(bool isWhitePlayer)
{
    Init();

    isWhite    = isWhitePlayer;
    //isComputer = isAIComputerPlayer;

    delete goldText;

    if (isWhite)
    {
        nobilityText = new Text(String(totalNobility), 20, 560);
        goldText = new Text("White Gold: " + String(gold), 20, 768 - 160);
        goldText->y = 100;

        *buttonReady->matrix.y = 768 - 140;
    }
    else
    {
        nobilityText = new Text(String(totalNobility), 20, 160);
        goldText = new Text("Black Gold: " + String(gold), 52, 112);
        *buttonReady->matrix.y = 35;
    }

    *buttonReady->matrix.x = renderer->windowWidth - 170;
    goldText->x = 20;
}

void Player::Init()
{
    //isComputer = false;
    isWhite    = false;
    isReady    = false;
    gold       = 4000;
    score      = 0;

    buttonReady = new Sprite("data/ButtonReady.png", 0.0f, 0.0f, 1.5f, 1.5f);
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
    nobilityText = new Text(String(totalNobility), x, y);
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

void Player::UpdateHand()
{
    if (piecesInHand.Empty() == false)
    {
        int x = 150;
        int y = 35;

        if (isWhite)
        {
            y = 768 - 95;
        }

        LinkedList<Piece*>::Iterator piece = piecesInHand.Begin();

        for (; piece != NULL; ++piece)
        {
            (*piece)->listNode = piece.curNode;
            *(*piece)->icon->matrix.x = x;
            *(*piece)->icon->matrix.y = y;
            (*piece)->Update();

            x += 50;
            if (x > renderer->windowWidth - 100)
            {
                y += 30;
                x = 50;
            }
        }
    }
}

void Player::Update()
{
    if (piecesInHand.Empty() == false)
    {
        totalNobility = 0;

        if (activePiece == nullptr)
        {
            activePiece = *piecesInHand.Begin().Item();
        }

        UpdateHand();

        LinkedList<Piece*>::Iterator piece = piecesInHand.Begin();

        for (; piece != NULL; ++piece)
        {
            if ((*piece)->icon->IsPressed())
            {
                activePiece = (*piece);
            }

            totalNobility += (*piece)->nobility;
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
