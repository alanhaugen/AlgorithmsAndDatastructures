#ifndef SHOP_H
#define SHOP_H

#include <core/components/component.h>
#include <core/containers/array.h>
#include <core/containers/stack.h>
#include <core/containers/linkedlist.h>
#include <core/components/sprite.h>
#include "piece.h"

class Shop : public Component
{
public:
    Shop();

    Stack<Piece*> shopItems;

    Sprite* background;
    LinkedList<Piece*> items;
    Piece* wildcardPiece = nullptr;
    Sprite* shopFront    = nullptr;
    Piece* activePiece   = nullptr;

    const int PIECE_TYPES_QUANTITY = 16;

    Piece* CreateRandomPiece();
    void SetShopPiecesToWhite(bool isWhite);
    void StockShopFront();
    void Update();
};

#endif
