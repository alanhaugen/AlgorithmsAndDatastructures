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

    LinkedList<Piece*> unshuffledDeckOfCards;

    bool isWhitesTurn;

    const int WildcardCost = 100;

    LinkedList<Piece*> itemsStoreFront;
    Piece* wildcardPiece = nullptr;
    Sprite* shopFront    = nullptr;
    Sprite* randomCard   = nullptr;
    Text* costTextRandomCard;
    Piece* activePiece   = nullptr;

    const int PIECE_TYPES_QUANTITY = 16;

    Piece* CreateRandomPiece();
    void SetShopPiecesToWhite(bool isWhite);
    void StockShopFront();
    Piece* CreateKing();
    Piece* CreateQueen();
    Piece* CreatePrince();
    Piece* CreatePrincess();
    Piece* CreateMonster();
    Piece* CreateBishop();
    Piece* CreateHydra();
    Piece* CreateKnight();
    Piece* CreatePeasant();
    Piece* CreateRogue();
    Piece* CreateStallion();
    Piece* CreateJester();
    Piece* CreateDeserter();
    Piece* CreateCannon();
    Piece* CreateShieldMan();
    Piece* CreateFence();

    void Update();
};

#endif
