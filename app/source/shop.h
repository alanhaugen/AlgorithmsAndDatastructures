#ifndef SHOP_H
#define SHOP_H

#include <core/components/component.h>
#include <core/containers/array.h>
#include <core/containers/linkedlist.h>
#include <core/components/sprite.h>
#include "piece.h"

class Shop : public Component
{
public:
    Shop();

    Array<Piece> possiblePieces;
    LinkedList<Piece*> pieces;
    Piece* wildcardPiece;
    Sprite* shopFront;

    Piece* activePiece;

    void Update();
};

#endif
