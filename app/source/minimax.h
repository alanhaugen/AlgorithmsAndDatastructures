#ifndef MINIMAX_H
#define MINIMAX_H

#include "tree.h"
#include "move.h"

class Minimax
{
private:
    class PieceState
    {
    private:
        Move move;

    public:
        bool isMax;

        PieceState()
        {
            isMax = false;
        }
    };

    Tree<PieceState> gameTree;

public:
    Minimax();

    // To make a minimax tree, you need to use an algorithm called a heuristic algorithm
    // A heuristic is really just a fancy word that means general rule of thumb.
    // Different AIs for different games have different heuristic functions for different purposes.
    // The job of a heuristic function is to look at a move in a game and evaluate if it is a good move or a bad move.
    // Source: Ron Penton, Data Structures for Games Programmers (2003)
    bool CalculateMiniMaxValue();
};

#endif // MINIMAX_H
