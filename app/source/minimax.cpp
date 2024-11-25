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
    // The best move in the end is the one where our opponent can screw us over the least.
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
            if ((*tile).piece->isWhite == opponent->isWhite)
            {
                nobility -= (*tile).piece->nobility; // min
            }
            else
            {
                nobility += (*tile).piece->nobility; // max
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

    LinkedList<Tree<Minimax::GameState *>::Node *>::Iterator node = gameTree.nodes.Begin();
    Tree<Minimax::GameState *>::Node* bestNode = NULL;

    // Loop through the entire tree and find the best node
    // Each player chooses the option that benefits them,
    // one always trying to make the score more positive (maximizing) or more negative (minimizing).
    for (; node != NULL; ++node)
    {
        // Set a new best node
        if ((*node)->children.Empty() == true)
        {
            if (bestNode == NULL)
            {
                bestNode = (*node);
            }

            // Max will want the biggest possible heuristic score
            if ((*node)->data->isMax == true)
            {
                if ((*node)->data->nobility > bestNode->data->nobility)
                {
                    bestNode = (*node);
                }
            }
            // Min will want the smallest possible heuristic score
            else
            {
                if ((*node)->data->nobility < (*node)->data->nobility)
                {
                    bestNode = (*node);
                }
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
    // Do moves of all layers above
    Tree<Minimax::GameState*>::Node* traversalNode = node;
    LinkedList<Tree<Minimax::GameState *>::Node *> previousNodes;

    // The root node will not have any moves to execute
    if (node != nullptr)
    {
        // Do all previous moves in the tree. Start by going back through the tree and store nodes
        while (traversalNode != NULL)
        {
            previousNodes.Append(traversalNode);
            traversalNode = traversalNode->parent;
        }

        // Go back and do all moves up to this point
        LinkedList<Tree<Minimax::GameState *>::Node *>::Iterator iterator = previousNodes.End();

        while (iterator != NULL)
        {
            (*iterator)->data->move.Execute();

            if (iterator.curNode->GetPrev() == NULL)
            {
                break;
            }

            iterator.curNode = iterator.curNode->GetPrev();
        }
    }

    // Get moves from current depth of the tree
    Array<Move> moves = player->GetAllPossibleMoves(gameBoard);

    // Put all the moves into a game tree to a given depth
    for (unsigned int i = 0; i < moves.Size(); i++)
    {
        Tree<GameState*>::Node* state = gameTree.AddNode(new GameState(moves[i], player == opponent));
        state->data->nobility = CalculateMiniMaxValue(gameBoard, moves[i]);
        state->data->depth = depth;

        state->parent = node;

        // The root is nullptr for a game tree
        if (node != nullptr)
        {
            node->children.Append(state);
        }
        // Add state to the root of the tree
        else
        {
            gameTree.rootChildren.Append(state);
        }
    }

    // Undo all the layers obove moves
    if (node != nullptr)
    {
        // Undo all previous moves in the tree
        LinkedList<Tree<Minimax::GameState *>::Node *>::Iterator iterator = previousNodes.Begin();

        while (iterator != NULL)
        {
            (*iterator)->data->move.Undo();

            if (iterator.curNode->GetNext() == NULL)
            {
                break;
            }

            iterator.curNode = iterator.curNode->GetNext();
        }
    }
}
