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
        LinkedList<Tree<Minimax::GameState *>::Node *>::Iterator node = gameTree.nodes.Begin();

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
            if (parentNode == nullptr)
            {
                parentNode = *gameTree.nodes.Begin();
                node = gameTree.nodes.Begin();
            }
            else
            {
                parentNode = ++(*node);
            }

            // Add entire next layer (add to each child of the previous layer)
            for (unsigned int j = 0; j < parentNode->children.Size(); j++)
            {
                // Add layer to tree
                AddLayer(gameBoard, parentNode->children[j], currentPlayer, i);
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
    int bestLevel = 0;
    int bestNobility = 0;

    LinkedList<Tree<Minimax::GameState *>::Node *>::Iterator node = gameTree.nodes.Begin();

    for (; node != NULL; ++node)
    {
        if ((*node)->data->depth > bestLevel)
        {
            bestNobility = 0;
        }

        if ((*node)->data->depth >= bestLevel && (*node)->data->isWhite == proponent->isWhite)
        {
            bestLevel = (*node)->data->depth;

            if ((*node)->data->nobility > bestNobility)
            {
                bestMove = (*node)->data->move;
            }
        }
    }

    return bestMove;
}

void Minimax::AddLayer(Board* gameBoard, Tree<Minimax::GameState*>::Node* node, Player* player, int depth)
{
    // Get moves from current depth of the tree
    Array<Move> moves = player->GetAllPossibleMoves(gameBoard);

    // Do the layer above's move
    node->data->move.Execute();

    // Loop through all nodes on a childless level on the tree
    for (unsigned int i = 0; i < node->children.Size(); i++)
    {
        // Put all the moves into a game tree to a given depth
        for (unsigned int j = 0; j < moves.Size(); j++)
        {
            Tree<GameState*>::Node* state = gameTree.AddNode(new GameState(moves[j], player->isWhite));
            state->data->nobility = CalculateMiniMaxValue(gameBoard, moves[j]);
            state->data->depth = depth;

            state->parent = node;
            node->children.Add(state);
        }
    }

    // Undo the layer obove's move
    node->data->move.Undo();
}
