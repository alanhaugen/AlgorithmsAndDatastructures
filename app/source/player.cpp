#include "player.h"

Player::Player()
{
    Init(true);
}

Player::Player(bool isWhitePlayer)
{
    Init(isWhitePlayer);
}

void Player::Init(bool isWhite_)
{
    isWhite  = isWhite_;
    isReady  = false;
    gold     = 1000;
    score    = 0;
    nobility = 0;

    buttonReady = new Sprite("data/B_Ready.png", 0.0f, 0.0f, 0.5f, 0.5f);
    goldText    = new Text("");

    activePiece = nullptr;

    delete goldText;

    if (isWhite)
    {
        nobilityText = new Text(String(nobility), 49, renderer->windowHeight - 227, 1, 1, glm::vec2(0.5, 0));
        goldText = new Text(String(gold), 125, renderer->windowHeight - 135);
        goldText->y = 100;

        *buttonReady->matrix.y = renderer->windowHeight - buttonReady->height*buttonReady->scaleY - 10;
    }
    else
    {
        nobilityText = new Text(String(nobility), 49    , 222, 1, 1, glm::vec2(0.5, 0));
        goldText = new Text(String(gold), 125, 105);
        *buttonReady->matrix.y = 10;
    }

    *buttonReady->matrix.x = renderer->windowWidth - 410;
    goldText->x = 20;
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

    UpdateNobilityText();
}

void Player::UpdateNobilityText()
{
    float x = *nobilityText->matrix.x;
    float y = *nobilityText->matrix.y;

    glm::vec2 anchorPoint = nobilityText->anchorPoint;

    delete nobilityText;
    nobilityText = new Text(String(nobility), x, y, 1, 1, anchorPoint);
    nobilityText->Update();
}

void Player::UpdateGoldText()
{
    int x = *goldText->matrix.x;
    int y = *goldText->matrix.y;

    delete goldText;

    if (isWhite)
    {
        goldText = new Text(String(gold), x, y);
    }
    else
    {
        goldText = new Text(String(gold), x, y);
    }

    goldText->Update();
}

void Player::RescalePiecesPlacing()
{
    if(placingStarted == true)
        return;

    LinkedList<Piece*>::Iterator piece = piecesInHand.Begin();

    for (; piece != NULL; ++piece)
    {
        (*piece)->icon->scaleX = 0.4;
        (*piece)->icon->scaleY = 0.4;
    }

    placingStarted = true;
}

void Player::UpdateHand()
{
    if (piecesInHand.Empty() == false)
    {
        int x = 180;
        int y = 16;

        LinkedList<Piece*>::Iterator piece = piecesInHand.Begin();


        if (isWhite)
        {
            y = renderer->windowHeight - y - (*piece)->icon->height * (*piece)->icon->scaleY;
        }

        for (; piece != NULL; ++piece)
        {
            (*piece)->listNode = piece.curNode;
            *(*piece)->icon->matrix.x = x;
            *(*piece)->icon->matrix.y = y;
            (*piece)->Update();


            x += (*piece)->icon->width * (*piece)->icon->scaleX;

            if(placingStarted == false)
            {
                if(piecesInHand.count > 15 && piecesInHand.count <=  21)
                {
                    if((*piece)->icon->scaleX >= 0.4)
                    {
                        (*piece)->icon->scaleX = 0.3;
                        (*piece)->icon->scaleY = 0.3;
                    }
                }
                if(piecesInHand.count > 20)
                {
                    if((*piece)->icon->scaleX >= 0.3)
                    {
                        (*piece)->icon->scaleX = 0.25;
                        (*piece)->icon->scaleY = 0.25;
                    }
                }
            }


//            if (piecesInHand.count > 15)
//            {
//                y += 30;
//                x = 50;
//            }
        }
    }
}

Array<Move> Player::GetAllPossibleMoves(Board* gameBoard, bool isFirstMove)
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
                moves += gameBoard->UpdateDots(&(*tile), false, false, isFirstMove == false);
            }
        }
    }

    return moves;
}

void Player::Update()
{
    if (piecesInHand.Empty() == false)
    {
        nobility = 0;

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

            nobility += (*piece)->nobility;
        }
    }

    if (isReady == false)
    {
        if (piecesInHand.Empty() == false)
        {
            buttonReady->Update();
        }

        nobilityText->Update();
    }

    goldText->Update();
}

Move Player::GetNextMove(Board *gameBoard, bool isFirstMove)
{
    // Check what the user has clicked on the game board
    if (input.Mouse.Pressed)
    {
        bool deselect = false;
        if(clickedTile != nullptr && clickedTile->piece != activePiece)
        {
            deselect = true;
        }
        clickedTile = gameBoard->GetBoardTileUnderMouse();

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
                gameBoard->UpdateDots(clickedTile, true, false, isFirstMove == false);
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
        if (activePiece != nullptr && deselect == false)
        {
            // Make a list of all the possible moves
            GetAllPossibleMoves(gameBoard, isFirstMove);

            // Check if the move is in the list of possible moves
            for (unsigned int i = 0; i < moves.Size(); i++)
            {
                bool legalTileClicked = false;

                if (moves[i].captureTile1 != nullptr && moves[i].movedPiece->isHydra == false)
                {
                    legalTileClicked = (moves[i].tileToMoveTo->x == clickedTile->x || moves[i].captureTile1->x == clickedTile->x) &&
                            (moves[i].tileToMoveTo->y == clickedTile->y || moves[i].captureTile1->y == clickedTile->y);
                }
                else
                {
                    legalTileClicked = moves[i].tileToMoveTo->x == clickedTile->x &&
                                       moves[i].tileToMoveTo->y == clickedTile->y;
                }

                if (legalTileClicked &&
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
