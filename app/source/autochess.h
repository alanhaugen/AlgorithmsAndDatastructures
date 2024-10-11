#ifndef AUTOCHESS_H
#define AUTOCHESS_H

#include <core/x-platform/scene.h>
#include <core/containers/stack.h>
#include "cursor.h"
#include "player.h"
#include "board.h"
#include "shop.h"

enum GameState
{
    Shopping,
    Placing,
    Playing,
    Done
};

class Autochess : public IScene
{
public:
    Autochess();
    Cursor* cursor;
    Board* gameBoard;
    Shop* shop;
    LinkedList<Move> history;
    Array<Move> moves;
    bool swapPlayers;

    Text* playerWhiteWins;
    Text* playerBlackWins;
    bool isAnyWhitePieces;
    bool isAnyBlackPieces;

    ITime* time;

    Piece* activePiece;

    Array<Player*> players;
    Player* white;
    Player* black;
    Player* activePlayer;

    void NextPlayer();

    bool isWhitesTurn;

    GameState state;

    void Init();
    void SetTile(Tile* tile);
    void Update();
};

#endif
