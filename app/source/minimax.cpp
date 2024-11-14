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

        // Put all the moves into a game tree to a given depth
        for (unsigned int j = 0; j < moves.Size(); j++)
        {
            moves[j].Execute();

            gameTree.AddNode(new GameState(moves[j], CalculateMiniMaxValue(gameBoard)));

            moves[j].Undo();
        }

        // Swap players and calculate the opponents possible states
        Player* temp = opponent;
        opponent     = proponent;
        proponent    = temp;
    }

    return Move();
}
