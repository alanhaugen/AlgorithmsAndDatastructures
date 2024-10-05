#include "shop.h"

Shop::Shop()
{
    possiblePieces.Add(new Piece("King",
                                 "data/Piece-WhiteRook.png",
                                 "Moves like a king in chess. Can move 1 tile in any direction.",
                                 200,
                                 10));
    possiblePieces.Add(new Piece("Prince",
                                 "data/Piece-WhiteRook.png",
                                 "Can move 4 tiles forwards/back/left/right, then attack left/right diagonal. Can jump over fences.",
                                 90,
                                 6));
    possiblePieces.Add(new Piece("Princess",
                                 "data/Piece-WhiteRook.png",
                                 "Moves like a queen in chess. Can move 3 tiles in any direction. Transformer. Can acquire the qualities of adjacent friendly pieces at will.",
                                 120,
                                 8));
    possiblePieces.Add(new Piece("Shield Man",
                                 "data/Piece-WhiteRook.png",
                                 "Can move 1 tile forward or 1 tile sideways. This piece cannot capture other pieces. The tile in front will become heavy.",
                                 50,
                                 1));
    possiblePieces.Add(new Piece("Queen",
                                 "data/Piece-WhiteRook.png",
                                 "Moves like a queen in chess.",
                                 150,
                                 5));
    possiblePieces.Add(new Piece("Monster",
                                 "data/Piece-WhiteRook.png",
                                 "Can move into any adjacent square for 5 tiles.",
                                 150,
                                 0));
    possiblePieces.Add(new Piece("Peasant",
                                 "data/Piece-WhiteRook.png",
                                 "Only move forward by 1 space, can capture if there is an opponent piece on that space.",
                                 20,
                                 0));
    possiblePieces.Add(new Piece("Knight",
                                 "data/Piece-WhiteRook.png",
                                 "Moves like a rook, but only 5 tiles forwards (or backwards or ot the side)",
                                 50,
                                 2));
    possiblePieces.Add(new Piece("Bishop",
                                 "data/Piece-WhiteRook.png",
                                 "Moves like a bishop. Can move unlimited amount of spaces diagonally in any direction.",
                                 80,
                                 4));
    possiblePieces.Add(new Piece("Stallion",
                                 "data/Piece-WhiteRook.png",
                                 "Moves like a knight in chess. Either two steps forward and one to the side, or one step forward and two to the side. Can jump over fences.",
                                 60,
                                 1));
    possiblePieces.Add(new Piece("Jester",
                                 "data/Piece-WhiteRook.png",
                                 "Moves diagonally 2 spaces in any direction.",
                                 75,
                                 3));
    possiblePieces.Add(new Piece("Fence",
                                 "data/Piece-WhiteRook.png",
                                 "Can be placed on the edge of tiles, is 3 spaces long. Blocks non-jumping pieces from passing. CAn only be placed horizontally.",
                                 40,
                                 0));
    possiblePieces.Add(new Piece("Hydra",
                                 "data/Piece-WhiteRook.png",
                                 "Can only move 1 space at the time. Can attack up to 3 adjacent enemies.",
                                 180,
                                 1));
    possiblePieces.Add(new Piece("Rogue",
                                 "data/Piece-WhiteRook.png",
                                 "Can move 2 tiles in any direction. If the rogue eliminates an enemy piece, the rogue moves back to its original position.",
                                 200,
                                 2));
    possiblePieces.Add(new Piece("Cannon",
                                 "data/Piece-WhiteRook.png",
                                 "Can move 1 space in any direction. Can shoot a cannon ball straight forwards. TYhe cannon ball can only hit the 4th and 5th space infront of the cannon. After use, the cannon is removed from the board.",
                                 350,
                                 1));

    int y = 430;
    for (int i = 0; i < 10; i++)
    {
        Piece* piece = possiblePieces[i];

        if (i > 0 && i % 5 == 0)
        {
            y += 30;
        }

        *piece->icon->matrix.x = 140 + ((i % 5) * 50);
        *piece->icon->matrix.y = y;

        pieces.Append(piece);//random.RandomRange(0, 14)]);
    }
}

void Shop::Update()
{
    if (pieces.Empty() == false)
    {
        LinkedList<Piece*>::Iterator piece = pieces.Begin();

        for (; piece != pieces.End(); ++piece)
        {
            if ((*piece)->icon->IsPressed())
            {
                activePiece = (*piece);
                activePiece->listNode = piece.curNode;
            }

            (*piece)->icon->Update();
        }
    }
}
