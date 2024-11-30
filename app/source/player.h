#ifndef PLAYER_H
#define PLAYER_H

#include <core/components/component.h>
#include <core/components/sprite.h>
#include <core/containers/array.h>
#include <core/components/text.h>
#include "piece.h"
#include "board.h"

class Player : public Component
{
public:
    LinkedList<Piece*> piecesInHand;
    int score;
    int gold;
    bool isWhite;
    Sprite* avatar;
    Sprite* buttonReady;
    Sprite* buttonReadyGray;


    bool isActivePlayer = false;
    bool isReady;
    bool placingStarted = false;

    Text* goldText;
    Text* nobilityText;

    Piece* activePiece;
    Array<Move> moves;
    int nobility;

    Tile* clickedTile = nullptr;

    Player();
    Player(bool isWhitePlayer);

    void Init(bool isWhite);
    void RecalculateNobility(Board *gameBoard);
    void UpdateNobilityText();
    void UpdateGoldText();
    void UpdateHand();
    Array<Move> GetAllPossibleMoves(Board* gameBoard, bool isFirstMove = false);

    void Update();
    Move GetNextMove(Board* gameBoard, bool isFirstMove = true);
    void RescalePiecesPlacing();
};

#endif
