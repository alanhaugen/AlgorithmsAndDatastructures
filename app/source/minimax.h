#ifndef MINIMAX_H
#define MINIMAX_H

#include "tree.h"
#include "move.h"

class Minimax
{
private:
    Tree<Move> gameTree;

public:
    Minimax();
};

#endif // MINIMAX_H
