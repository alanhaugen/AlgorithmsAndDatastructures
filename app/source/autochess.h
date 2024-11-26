#ifndef AUTOCHESS_H
#define AUTOCHESS_H

#include <core/x-platform/scene.h>
#include <core/containers/stack.h>
#include "cursor.h"
#include "player.h"
#include "aiplayer.h"
#include "board.h"
#include "shop.h"
#include "rulebook.h"
#include "settings.h"

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
    Shop* shop = nullptr;
    ITime* infoBoardTimer;

    Rulebook* rules;
    Settings* settings;

    Sprite* volumeControl;
    bool isMuted = false;

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

    Text* settingsText;
    Text* rulebookText;
    Text* backArrowText;
    Text* undoButtonText;
    Text* whiteNobilityText;
    Text* blackNobilityText;
    Text* turnsLeftText1;
    Text* turnsLeftText2;

    bool isDraw;
    bool replayAdded;

    Sprite* goldIcon1;
    Sprite* goldIcon2;

    Sprite* backArrow;
    Sprite* undoButton;

    Sprite* whitePiecesBanner;
    Sprite* blackPiecesBanner;
    Sprite* goldBackground;

    Sprite* nobilityIcon1;
    Sprite* nobilityIcon2;

    Sprite* blueBanner;
    Sprite* yellowBanner;
    Sprite* turnsLeftBanner;
    Sprite* victoryBanner;
    Sprite* returnToMainMenu;
    Sprite* watchReplay;
    Sprite* autoPlacePieces;
    Sprite* autoPlaceAllPieces;

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

    bool PopUpOpen = false;

    void checkForPopUp();
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

    void searchTile(Tile* tile, Tile *startTile, Tile *endTile, bool &isDone, Array<Tile *> &searchTiles, Tree<Tile *>& searchTree);

    Move animatedMove;
    glm::vec2 prevpos;
    glm::vec2 nextpos;

    // This will start as the final node in the tree
    Tree<Tile*>::Node* activeNode = NULL;

    Stack<glm::vec2> animationMoveStack;
};

#endif
