#include "cursor.h"

Cursor::Cursor()
{
    whiteCursor = new Sprite("data/WhiteCursor.png", 0, 0, 1.0, 1.0);
    blackCursor = new Sprite("data/BlackCursor.png", 0, 0, 1.0, 1.0);

    activeCursor = blackCursor;
}

void Cursor::Update()
{
    *activeCursor->matrix.x = input.Mouse.x - 5;
    *activeCursor->matrix.y = input.Mouse.y - 5;

    activeCursor->Update();
}

void Cursor::SetCursorToWhiteColour(bool isWhite)
{
    if (isWhite)
    {
        activeCursor = whiteCursor;
    }
    else
    {
        activeCursor = blackCursor;
    }
}
