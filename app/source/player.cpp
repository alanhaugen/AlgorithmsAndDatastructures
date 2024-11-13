#include "player.h"

Player::Player()
{
    Init();
}

Player::Player(bool isWhitePlayer)
{
    Init();

    isWhite    = isWhitePlayer;

    delete goldText;

    if (isWhite)
    {
        nobilityText = new Text(String(totalNobility), 20, 560);
        goldText = new Text("White Gold: " + String(gold), 20, 768 - 160);
        goldText->y = 100;

        *buttonReady->matrix.y = 768 - 140;
    }
    else
    {
        nobilityText = new Text(String(totalNobility), 20, 160);
        goldText = new Text("Black Gold: " + String(gold), 52, 112);
        *buttonReady->matrix.y = 35;
    }

    *buttonReady->matrix.x = renderer->windowWidth - 170;
    goldText->x = 20;
}

void Player::Init()
{
    //isComputer = false;
    isWhite    = false;
    isReady    = false;
    gold       = 1000;
    score      = 0;

    buttonReady = new Sprite("data/ButtonReady.png", 0.0f, 0.0f, 1.5f, 1.5f);
    goldText    = new Text("");

    activePiece = nullptr;

    totalNobility = 0;
}

void Player::RecalculateNobility(Board* gameBoard)
{
    nobility = 0;

    LinkedList<Tile>::Iterator tile = gameBoard->tiles.Begin();

    for (; tile != NULL; ++tile)
    {
        if ((*tile).piece != nullptr)
        {
            if ((*tile).piece->isWhite == isWhite)
            {
                nobility += tile->piece->nobility;
                moves += gameBoard->UpdateDots(&(*tile), false);
            }
        }
    }

    UpdateNobilityText(nobility);
}

void Player::UpdateNobilityText(int nobility)
{
    if (nobility == -1)
    {
        Update();
    }
    else
    {
        totalNobility = nobility;
    }

    int x = *nobilityText->matrix.x;
    int y = *nobilityText->matrix.y;

    delete nobilityText;
    nobilityText = new Text(String(totalNobility), x, y);
    nobilityText->Update();
}

void Player::UpdateGoldText()
{
    int x = *goldText->matrix.x;
    int y = *goldText->matrix.y;

    delete goldText;

    if (isWhite)
    {
        goldText = new Text("White Gold: " + String(gold), x, y);
    }
    else
    {
        goldText = new Text("Black Gold: " + String(gold), x, y);
    }

    goldText->Update();
}

void Player::UpdateHand()
{
    if (piecesInHand.Empty() == false)
    {
        int x = 150;
        int y = 35;

        if (isWhite)
        {
            y = 768 - 95;
        }

        LinkedList<Piece*>::Iterator piece = piecesInHand.Begin();

        for (; piece != NULL; ++piece)
        {
            (*piece)->listNode = piece.curNode;
            *(*piece)->icon->matrix.x = x;
            *(*piece)->icon->matrix.y = y;
            (*piece)->Update();

            x += 50;
            if (x > renderer->windowWidth - 100)
            {
                y += 30;
                x = 50;
            }
        }
    }
}

Array<Move> Player::GetAllPossibleMoves(Board* gameBoard)
{
    moves.Clear();

    // Loop through the game board and find all possible moves for player
    LinkedList<Tile>::Iterator tile = gameBoard->tiles.Begin();

    for (; tile != NULL; ++tile)
    {
        if ((*tile).piece != nullptr)
        {
            if ((*tile).piece->isWhite == isWhite)
            {
                moves += gameBoard->UpdateDots(&(*tile), false);
            }
        }
    }

    return moves;
}

void Player::Update()
{
    if (piecesInHand.Empty() == false)
    {
        totalNobility = 0;

        if (activePiece == nullptr)
        {
            activePiece = *piecesInHand.Begin().Item();
        }

        UpdateHand();

        LinkedList<Piece*>::Iterator piece = piecesInHand.Begin();

        for (; piece != NULL; ++piece)
        {
            if ((*piece)->icon->IsPressed())
            {
                activePiece = (*piece);
            }

            totalNobility += (*piece)->nobility;
        }
    }

    if (isReady == false)
    {
        if (piecesInHand.Empty() == false)
        {
            buttonReady->Update();
        }

        goldText->Update();
        nobilityText->Update();
    }
}

Move Player::GetNextMove(Board *gameBoard)
{
    // Check what the user has clicked on the game board
    if (input.Mouse.Pressed)
    {
        Tile* clickedTile = gameBoard->GetBoardTileUnderMouse();

        // IF the user has not selected anything, return without a move
        if (clickedTile == nullptr)
        {
            return Move();
        }

        // Highlight the tile the user has selected
        gameBoard->highlight->Show();

        // Check if user has clicked on tile with a piece
        if (clickedTile->piece != nullptr)
        {
            // Activate piece clicked on
            if (isWhite == clickedTile->piece->isWhite)
            {
                activePiece = clickedTile->piece;
                gameBoard->HideDots();
                gameBoard->UpdateDots(clickedTile, true);
            }
            else
            {
                moves.Clear();
                gameBoard->HideDots();
            }
        }
        else
        {
            moves.Clear();
            gameBoard->HideDots();
        }

        // Try to make a move
        if (activePiece != nullptr)
        {
            // Make a list of all the possible moves
            GetAllPossibleMoves(gameBoard);

            // Check if the move is in the list of possible moves
            for (unsigned int i = 0; i < moves.Size(); i++)
            {
                if ((moves[i].tileToMoveTo->x == clickedTile->x &&
                     moves[i].tileToMoveTo->y == clickedTile->y) &&
                        (moves[i].oldTile->x == activePiece->currentTile->x &&
                         moves[i].oldTile->y == activePiece->currentTile->y))
                {
                    // Make the move
                    gameBoard->highlight->Hide();
                    gameBoard->HideDots();

                    // Deselect the selected piece
                    activePiece = nullptr;

                    return moves[i];
                }
            }
        }
    }

    // No move was made, return a move with movedPiece equals nullptr
    return Move();
}
