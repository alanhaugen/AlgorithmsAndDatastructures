#ifndef AUTOCHESS_H
#define AUTOCHESS_H

#include <core/x-platform/scene.h>
#include <core/containers/stack.h>
#include "cursor.h"
#include "player.h"
#include "aiplayer.h"
#include "board.h"
#include "shop.h"

enum GameState
{
    Shopping,
    Placing,
    Playing,
    Done,
    Animate
};

const int MovesTotal = 20;

class Autochess : public IScene
{
public:
    Autochess();
    Camera* cam;
    Cursor* cursor;
    Board* gameBoard;
    Shop* shop;
    ITime* infoBoardTimer;

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

    Sprite* backArrow;
    Sprite* undoButton;

    Sprite* whitePiecesBanner;
    Sprite* blackPiecesBanner;

    Sprite* blueBanner;
    Sprite* yellowBanner;
    Sprite* turnsLeftBanner;
    Sprite* victoryBanner;

    Sprite* background;

    Piece* activePiece;

    Array<Player*> players;
    Player* white;
    Player* black;
    Player* activePlayer;
    Player* opponentPlayer;

    Sprite* activeInfoBoard = nullptr;

    void NextPlayer();

    bool isWhitesTurn;

    int hydraAttacks;

    GameState state;

    void Init();
    void SetTile(Tile* tile);
    void Update();
    void UpdateShop();
    void UpdatePlacing();
    void UpdatePlaying();
    void UpdateDone();
    void UpdateAnimation();
    GameState IsGameDone();

    void UpdateInfoBoardShop();
    void UpdateInfoBoard();

    void Animate(Move move);

    Move  animatedPiece;
    glm::vec2 startpos;
    glm::vec2 endpos;
};

#endif
