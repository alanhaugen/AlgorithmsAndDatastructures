#ifndef shop_H
#define shop_H

#include <core/components/component.h>
#include <core/containers/array.h>
#include <core/containers/linkedlist.h>
#include <core/components/sprite.h>
#include "piece.h"

class shop : public Component
{
public:
    shop();

    Array<Piece*> possiblePieces;
    LinkedList<Piece*> pieces;
    Piece* wildcardPiece;
    Sprite* shopFront;

    void Update();
    void UpdateAfterPhysics();
};

#endif
