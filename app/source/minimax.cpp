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
        }
        else
        {
            // Set parent node for current depth by iteration
            if (parentNode != nullptr)
            {
                //parentNode = parentNode->parent;
            }
        }

        /*for (int j = 0; j < parentNode->children.Size())
        {

        }*/

        // Add layer to tree
        AddLayer(gameBoard, parentNode, currentPlayer);

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

    return Move();
}

void Minimax::AddLayer(Board* gameBoard, Tree<Minimax::GameState*>::Node* node, Player* player)
{
    // Get moves from current depth of the tree
    Array<Move> moves = player->GetAllPossibleMoves(gameBoard);

    // Do the layer above's move
    node->data->move.Execute();

    // Loop through all nodes on a childless level on the tree
    for (int i = 0; i < node->children.Size(); i++)
    {
        // Put all the moves into a game tree to a given depth
        for (unsigned int j = 0; j < moves.Size(); j++)
        {
            Tree<GameState*>::Node* state = gameTree.AddNode(new GameState(moves[j], player->isWhite));
            state->data->nobility = CalculateMiniMaxValue(gameBoard, moves[j]);
            state->parent = node;
        }
    }

    // Undo the layer obove's move
    node->data->move.Undo();
}
