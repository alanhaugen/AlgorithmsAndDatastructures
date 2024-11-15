#include "minimax.h"

Minimax::Minimax()
{

}

bool Minimax::CalculateMiniMaxValue(Board* gameBoard)
{
    // Our heuristic will be maximizing one's collective nobility,
    // and for the opponent minimizing the opponents collective nobility
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

                gameTree.AddNode(new GameState(moves[j], CalculateMiniMaxValue(gameBoard)));
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
