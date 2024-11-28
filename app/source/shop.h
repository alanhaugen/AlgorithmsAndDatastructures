#ifndef SHOP_H
#define SHOP_H

#include <core/components/component.h>
#include <core/containers/array.h>
#include <core/containers/stack.h>
#include <core/containers/linkedlist.h>
#include <core/components/sprite.h>
#include "piece.h"

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
Piece* CreateRook();
Piece* CreateRock();
Piece* CreateTree();
Piece* CreateWater();
Piece* CreateRiver();

class Shop : public Component
{
public:
    Shop();

    Stack<Piece*> shopItems;

    LinkedList<Piece*> unshuffledDeckOfCards;
    LinkedList<Piece*> obstacleCards;

    bool isWhitesTurn;

    bool PopUpOpen = false;

    const int WildcardCost = 100;

    const int RestockShopCost = 50;
    const bool RestockShopNextPlayer = true;

    LinkedList<Piece*> itemsStoreFront;
    Piece* wildcardPiece = nullptr;
    Sprite* shopFront    = nullptr;
    Sprite* randomCard   = nullptr;
    Sprite* restockShop  = nullptr;

    Text* costTextRestockShop;
    Text* nameTextRestockShop;
    Text* nameTextRestockShop2;
    Text* costTextRandomCard;
    Text* randomCardText1;
    Text* randomCardText2;
    Piece* activePiece   = nullptr;


    const int PIECE_TYPES_QUANTITY = 17;

    Piece* CreateRandomPiece();
    void SetShopPiecesToWhite(bool isWhite);
    void StockShopFront();
    void DiscardShopFront();

    void Update();
};

#endif
