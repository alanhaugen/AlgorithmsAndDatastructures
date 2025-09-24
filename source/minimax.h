#ifndef MINIMAX_H
#define MINIMAX_H

#include "tree.h"
#include "move.h"
#include "player.h"

class Minimax
{
private:
    class GameState
    {
    public:
        Move move;
        bool isMax;
        int nobility;

        int depth;

        GameState()
        {
        }

        GameState(Move move_, bool isMax_)
        {
            move  = move_;
            isMax = isMax_;
        }
    };

    Tree<GameState*> gameTree;

public:
    Minimax();

    Player* proponent;
    Player* opponent;

    // To make a minimax tree, you need to use an algorithm called a heuristic algorithm
    // A heuristic is really just a fancy word that means general rule of thumb.
    // Different AIs for different games have different heuristic functions for different purposes.
    // The job of a heuristic function is to look at a move in a game and evaluate if it is a good move or a bad move.
    // Source: Ron Penton, Data Structures for Games Programmers (2003)
    int CalculateMiniMaxValue(Board *gameBoard, Move move);
    Move FindBestMove(Player* min, Player* max, Board* gameBoard, int depth, bool isFirstMove);
    void AddLayer(Board* gameBoard, Tree<Minimax::GameState*>::Node* node, Player* player, int depth, bool isFirstMove);
};

#endif // MINIMAX_H
