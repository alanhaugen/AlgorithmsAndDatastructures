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

    players[1].isWhite = false;

    cursor = new Cursor();
    cursor->SetCursorToWhiteColour(true);
    components.Add(cursor);
}

void Autochess::Update()
{
    gameBoard->Update();
    shop->Update();

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
