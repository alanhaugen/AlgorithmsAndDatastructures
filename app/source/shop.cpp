#include "shop.h"

Shop::Shop()
{
    /*possiblePieces = Array<Piece>(15);

    possiblePieces[0] = Piece("King",
                              "data/Piece-WhiteRook.png",
                              "Moves like a king in chess. Can move 1 tile in any direction.",
                              200,
                              10);
    possiblePieces[1] = Piece("Prince",
                              "data/Piece-WhiteRook.png",
                              "Can move 4 tiles forwards/back/left/right, then attack left/right diagonal. Can jump over fences.",
                              90,
                              6);
    possiblePieces[2] = Piece("Princess",
                              "data/Piece-WhiteRook.png",
                              "Moves like a queen in chess. Can move 3 tiles in any direction. Transformer. Can acquire the qualities of adjacent friendly pieces at will.",
                              120,
                              8);
    possiblePieces[3] = Piece("Shield Man",
                              "data/Piece-WhiteRook.png",
                              "Can move 1 tile forward or 1 tile sideways. This piece cannot capture other pieces. The tile in front will become heavy.",
                              50,
                              1);
    possiblePieces[4] = Piece("Queen",
                              "data/Piece-WhiteRook.png",
                              "Moves like a queen in chess.",
                              150,
                              5);
    possiblePieces[5] = Piece("Monster",
                              "data/Piece-WhiteRook.png",
                              "Can move into any adjacent square for 5 tiles.",
                              150,
                              0);
    possiblePieces[6] = Piece("Peasant",
                              "data/Piece-WhiteRook.png",
                              "Only move forward by 1 space, can capture if there is an opponent piece on that space.",
                              20,
                              0);
    possiblePieces[7] = Piece("Knight",
                              "data/Piece-WhiteRook.png",
                              "Moves like a rook, but only 5 tiles forwards (or backwards or ot the side)",
                              50,
                              2);
    possiblePieces[8] = Piece("Bishop",
                              "data/Piece-WhiteRook.png",
                              "Moves like a bishop. Can move unlimited amount of spaces diagonally in any direction.",
                              80,
                              4);
    possiblePieces[9] = Piece("Stallion",
                              "data/Piece-WhiteRook.png",
                              "Moves like a knight in chess. Either two steps forward and one to the side, or one step forward and two to the side. Can jump over fences.",
                              60,
                              1);
    possiblePieces[10] = Piece("Jester",
                               "data/Piece-WhiteRook.png",
                               "Moves diagonally 2 spaces in any direction.",
                               75,
                               3);
    possiblePieces[11] = Piece("Fence",
                               "data/Piece-WhiteRook.png",
                               "Can be placed on the edge of tiles, is 3 spaces long. Blocks non-jumping pieces from passing. CAn only be placed horizontally.",
                               40,
                               0);
    possiblePieces[12] = Piece("Hydra",
                               "data/Piece-WhiteRook.png",
                               "Can only move 1 space at the time. Can attack up to 3 adjacent enemies.",
                               180,
                               1);
    possiblePieces[13] = Piece("Rogue",
                               "data/Piece-WhiteRook.png",
                               "Can move 2 tiles in any direction. If the rogue eliminates an enemy piece, the rogue moves back to its original position.",
                               200,
                               2);
    possiblePieces[14] = Piece("Cannon",
                               "data/Piece-WhiteRook.png",
                               "Can move 1 space in any direction. Can shoot a cannon ball straight forwards. TYhe cannon ball can only hit the 4th and 5th space infront of the cannon. After use, the cannon is removed from the board.",
                               350,
                               1);*/

    /*for (int i = 0; i < 10; i++)
    {
        Piece piece = possiblePieces[i];
        *piece.icon->matrix.x = 200 + (i * 50);
        *piece.icon->matrix.y = 300;

        pieces.Append(&piece);//random.RandomRange(0, 14)]);
    }*/

    activePiece = nullptr;
}

void Shop::Update()
{
    /*LinkedList<Piece*>::Iterator piece = pieces.Begin();

    for (; piece != pieces.End(); ++piece)
    {
        if ((*piece)->icon->IsPressed())
        {
            activePiece = (*piece);
        }

        (*piece)->icon->Update();
    }*/
}
