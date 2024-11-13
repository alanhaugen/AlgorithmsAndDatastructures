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
    //bool isComputer;

    bool isReady;

    int totalNobility;

    Text* goldText;
    Text* nobilityText;

    Piece* activePiece;
    Array<Move> moves;
    int nobility;

    Player();
    Player(bool isWhitePlayer);

    void Init();
    void RecalculateNobility(Board *gameBoard);
    void UpdateNobilityText(int nobility = -1);
    void UpdateGoldText();
    void UpdateHand();
    Array<Move> GetAllPossibleMoves(Board* gameBoard);

    void Update();
    Move GetNextMove(Board* gameBoard);
};

#endif
