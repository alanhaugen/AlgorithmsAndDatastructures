#include "autochess.h"

Autochess::Autochess()
{
}

void Autochess::Init()
{
    players = Array<Player>(2);
    gameBoard = new Board();
    shop = new Shop();
    isWhitesTurn = true;

    whiteCursor = new Sprite("data/WhiteCursor.png", 0, 0, 1.0, 1.0);
    blackCursor = new Sprite("data/BlackCursor.png", 0, 0, 1.0, 1.0);

    activeCursor = whiteCursor;
}

void Autochess::Update()
{
    gameBoard->Update();
    shop->Update();

    *activeCursor->matrix.x = input.Mouse.x;
    *activeCursor->matrix.y = input.Mouse.y;

    activeCursor->Update();

    /*if (input.Mouse.Pressed)
    {
        isWhitesTurn = !isWhitesTurn;

        if (isWhitesTurn)
        {
            activeCursor = whiteCursor;
        }
        else
        {
            activeCursor = blackCursor;
        }
    }*/
}

void Autochess::UpdateAfterPhysics()
{
}

