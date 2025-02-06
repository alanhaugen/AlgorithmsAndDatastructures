#ifndef CURSOR_H
#define CURSOR_H

#include <core/components/component.h>
#include <core/components/sprite.h>

class Cursor : public Component
{
public:
    Cursor();

    Sprite* whiteCursor;
    Sprite* blackCursor;
    Sprite* activeCursor;

    void Update();
    void UpdateAfterPhysics();

    void SetCursorToWhiteColour(bool isWhite);
};

#endif
