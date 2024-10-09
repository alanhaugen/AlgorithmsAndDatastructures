#ifndef AUTOCHESS_H
#define AUTOCHESS_H

#include <core/x-platform/scene.h>
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
    Queue<Move> replay;

    Piece* activePiece = nullptr;

    Array<Player*> players;
    Player* white;
    Player* black;
    Player* activePlayer;

    void NextPlayer();

    bool isWhitesTurn;

    GameState state = GameState::Shopping;

    void Init();
    void SetTile(Tile* tile);
    void Update();
};

#endif
