#include "minimax.h"

// Minimization-maximization algorithm
Minimax::Minimax()
{
}

bool Minimax::CalculateMiniMaxValue(Board* gameBoard)
{
    // Our heuristic will be that the best possible move for us is the one
    // which minimizes the opponents collective nobility,
    // and the opponent's best move is the one which minimizes our collective nobility

    // The best strategy is assuming the opponent always respond with the best possible move
    // The best move is the one where our opponent can screw us over the least.
    // Source: Ron Penton's book Data Structures for Game Programmers and chessengines.org

    // Loop through the board and calculate nobility
    //LinkedList<Tile>::Iterator tile = gameBoard->tiles.Begin();

    /*for (; tile != NULL; ++tile)
    {
        if ((*tile).piece != nullptr)
        {
        }
    }*/

    return false;
}

Move Minimax::FindBestMove(Player* min, Player* max, Board* gameBoard, int depth)
{
    gameTree.Clear();

    // Min goes first
    Player* proponent = min;
    Player* opponent  = max;

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
            // Go to the depth level we are at
            parentNode = gameTree.root;

            for (int i = 1; i < depth; i++)
            {
                // Set parent node for current depth by iteration
                if (parentNode != nullptr)
                {
                    parentNode = parentNode->parent;
                }
            }
        }

        // Get moves from current depth of the tree
        Array<Move> moves = proponent->GetAllPossibleMoves(gameBoard);

        // Loop through all nodes on a childless level on the tree
        //for (every childless node)
        //{
            //Tree<GameState>::Node *parent;
            // parent = node;
            // parent->data->Execute();

            // Put all the moves into a game tree to a given depth
            for (unsigned int j = 0; j < moves.Size(); j++)
            {
                moves[j].Execute();

                gameTree.AddNode(new GameState(moves[j], CalculateMiniMaxValue(gameBoard)), parentNode);
                // gameState.parent = parent;

                moves[j].Undo();
            }

            //parent->data->Undo();
        //}

        // Swap players and calculate the opponents possible states
        Player* temp = opponent;
        opponent     = proponent;
        proponent    = temp;
    }

    return Move();
}
