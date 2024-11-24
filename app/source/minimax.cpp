#include "minimax.h"

// Minimization-maximization algorithm
Minimax::Minimax()
{
}

int Minimax::CalculateMiniMaxValue(Board* gameBoard, Move move)
{
    // Our heuristic will be that the best possible move for us is the one
    // which minimizes the opponents collective nobility,
    // and the opponent's best move is the one which minimizes our collective nobility

    // The best strategy is assuming the opponent always respond with the best possible move
    // The best move is the one where our opponent can screw us over the least.
    // Source: Ron Penton's book Data Structures for Game Programmers and chessengines.org

    // Do the move
    move.Execute();

    // Loop through the board and calculate nobility
    LinkedList<Tile>::Iterator tile = gameBoard->tiles.Begin();

    int nobility = 0;

    for (; tile != NULL; ++tile)
    {
        if ((*tile).piece != nullptr)
        {
            if ((*tile).piece->isWhite == proponent->isWhite)
            {
                nobility += (*tile).piece->nobility;
            }
        }
    }

    // Undo the move for the next iteration
    move.Undo();

    return nobility;
}

Move Minimax::FindBestMove(Player* min, Player* max, Board* gameBoard, int depth)
{
    gameTree.Clear();

    // Min goes first
    proponent = min;
    opponent  = max;

    Player* currentPlayer = min;

    // The current node being filled
    Tree<GameState*>::Node* parentNode;

    // Fill the tree to a certain depth
    for (int i = 0; i < depth; i++)
    {
        if (i == 0)
        {
            // At the first layer, the root node is nullptr
            parentNode = nullptr;

            // Add the first layer to the tree
            AddLayer(gameBoard, parentNode, currentPlayer, i);
        }
        else
        {
            // We need to go through the entire tree at a level
            LinkedList<Tree<Minimax::GameState *>::Node *>::Iterator node = gameTree.nodes.Begin();

            for (; node != NULL; ++node)
            {
                if ((*node)->data->depth == (i - 1))
                {
                    parentNode = (*node);

                    // Add layer to tree
                    AddLayer(gameBoard, parentNode, currentPlayer, i);
                }
            }
        }

        // Swap players for the next layer of the tree
        if (currentPlayer == min)
        {
            currentPlayer = max;
        }
        else
        {
            currentPlayer = min;
        }
    }

    // Traverse the tree and find the best move
    Move bestMove;
    int bestLevel = -1;
    int bestNobility = -1;

    LinkedList<Tree<Minimax::GameState *>::Node *>::Iterator node = gameTree.nodes.Begin();
    Tree<Minimax::GameState *>::Node* bestNode = NULL;

    // Loop through the entire tree and find the best node
    for (; node != NULL; ++node)
    {
        if ((*node)->data->depth > bestLevel)
        {
            bestNobility = -1;
        }

        if ((*node)->data->depth >= bestLevel && (*node)->data->isWhite == proponent->isWhite)
        {
            bestLevel = (*node)->data->depth;

            if ((*node)->data->nobility > bestNobility)
            {
                bestNode = (*node);
            }
        }
    }

    // Get the top level node of this branch
    if (bestNode != NULL)
    {
        while (bestNode != NULL)
        {
            bestMove = bestNode->data->move;
            bestNode = bestNode->parent;
        }
    }

    return bestMove;
}

void Minimax::AddLayer(Board* gameBoard, Tree<Minimax::GameState*>::Node* node, Player* player, int depth)
{
    // Do the layer above's move
    int childrenQuantity = 1;

    if (node != nullptr)
    {
        // Do all previous moves in the tree
        /*while (bestNode != NULL)
        {
            bestMove = bestNode->data->move;
            bestNode = bestNode->parent;
        }*/

        node->data->move.Execute();
        childrenQuantity = node->children.Size();
    }

    // Get moves from current depth of the tree
    Array<Move> moves = player->GetAllPossibleMoves(gameBoard);

    // Loop through all nodes on a childless level on the tree
    for (int i = 0; i < childrenQuantity; i++)
    {
        // Put all the moves into a game tree to a given depth
        for (unsigned int j = 0; j < moves.Size(); j++)
        {
            Tree<GameState*>::Node* state = gameTree.AddNode(new GameState(moves[j], player->isWhite));
            state->data->nobility = CalculateMiniMaxValue(gameBoard, moves[j]);
            state->data->depth = depth;

            state->parent = node;

            if (node != nullptr)
            {
                node->children.Append(state);
            }
        }
    }

    // Undo the layer obove's move
    if (node != nullptr)
    {
        node->data->move.Undo();

        // Undo all previous moves in the tree
        /*while (bestNode != NULL)
        {
            bestMove = bestNode->data->move;
            bestNode = bestNode->parent;
        }*/
    }
}
