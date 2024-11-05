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

const int MovesTotal = 50;

class Autochess : public IScene
{
public:
    Autochess();
    Camera* cam;
    Cursor* cursor;
    Board* gameBoard;
    Shop* shop;
    LinkedList<Move> history;
    Stack<Text*> topPreviousMoves;
    Array<Move> moves;
    bool swapPlayers;

    int movesCompleted;

    Text* playerWhiteWins;
    Text* playerBlackWins;
    Text* playerDraw;
    bool isAnyWhitePieces;
    bool isAnyBlackPieces;

    Text* playerWhiteTurn;
    Text* playerBlackTurn;

    Text* movesLeftText;

    bool isDraw;
    bool replayAdded;

    Sprite* whitePiecesBanner;
    Sprite* blackPiecesBanner;

    Sprite* blueBanner;
    Sprite* yellowBanner;
    Sprite* turnsLeftBanner;
    Sprite* victoryBanner;

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
