#include "board.h"
#include "main.h"
#include "piece.h"

Board::Board()
{
    GenerateTiles();
    bg = new Sprite("data/bg.png", 403, 103, 0.7, 0.7);

    HideDots();
    highlight = new Sprite("data/TileBorder.png", 0, 0, tileScale, tileScale);
    highlight->Hide();

    // Adding board coords
    String chars[10] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j"};
    String nums[10] = {" 1", " 2", " 3", " 4", " 5", " 6", " 7", " 8", " 9", "10"};

    for (int i = 0; i < 10; i++)
    {
        components.Add(new Text(nums[i], 396, (140 + (i*52)) - 6, 0.75, 0.75));
        components.Add(new Text(chars[i], 430 + (i*50), 635, 0.75, 0.75));
    }
}

void Board::GenerateTiles()
{
    bool isWhiteTile = true;

    float scale = tileScale;

    Sprite* tile;
    tile = new Sprite("data/WhiteTile.png", 0, 0, scale, scale);

    float offsetX = (renderer->windowWidth / 2) - (tile->width * tile->scaleX  * 5);
    float offsetY = ((renderer->windowHeight / 2)) - (tile->height * tile->scaleY * 5); // renderer->windowHeight / 2

    delete tile;

    for (int y = 0; y < 10; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            Tile tile;
            tile.x = x;
            tile.y = 9 - y;

            Sprite* sprite;

            if (isWhiteTile)
            {
                sprite = new Sprite("data/WhiteTile.png", 0, 0, scale, scale);
            }
            else
            {
                sprite = new Sprite("data/BlackTile.png", 0, 0, scale, scale);
            }

            tile.moveDot = new Sprite("data/MoveDot.png", 0, 0, scale, scale);
            tile.attackBorder = new Sprite("data/TileBorder-Red.png", 0, 0, scale, scale);

            *sprite->matrix.x = x * (sprite->width  * sprite->scaleX) + offsetX;
            *sprite->matrix.y = y * (sprite->height * sprite->scaleY) + offsetY;

            tile.sprite = sprite;
            tiles.Append(tile);

            isWhiteTile = !isWhiteTile;
        }

        isWhiteTile = !isWhiteTile;
    }
}

void Board::HideDots()
{
    LinkedList<Tile>::Iterator tile = tiles.Begin();

    for (; tile != NULL; ++tile)
    {
        (*tile).moveDot->Hide();
        (*tile).attackBorder->Hide();
    }
}

Array<Move> Board::UpdateDots(Tile* tile, bool showDot, bool isCaptureOnly)
{
    int x = tile->x;
    int y = tile->y;

    Array<glm::vec2> pattern = tile->piece->movePattern;
    Array<Capture> capturePattern = tile->piece->captureOnlyMovePattern;

    LinkedList<Tile>::Iterator node = tiles.Begin();

    Array<Move> moves;

    int yDirectionInvert = 1;

    if (tile->piece->isWhite == false)
    {
        yDirectionInvert = -1;
    }

    // Calculate tile weights
    for (node = tiles.Begin(); node != NULL; ++node)
    {
        if ((*node).piece != nullptr)
        {
            if ((*node).piece->isWhite != tile->piece->isWhite &&(*node).piece->weightPattern.Empty() == false)
            {
                Array<glm::vec2> weightPattern = (*node).piece->weightPattern;

                LinkedList<Tile>::Iterator newNode = tiles.Begin();

                int x = (*node).x;
                int y = (*node).y;

                for (; newNode != NULL; ++newNode)
                {
                    // Add weight to board
                    for (unsigned int i = 0; i < weightPattern.Size(); i++)
                    {
                        if ((*newNode).x == x + weightPattern[i].x && (*newNode).y == y + (-yDirectionInvert * weightPattern[i].y))
                        {
                            (*newNode).weight = 1;
                        }
                    }
                }
            }
        }
    }

    if (tile->piece->isJumping)
    {
        for (node = tiles.Begin(); node != NULL; ++node)
        {
            for (unsigned int i = 0; i < pattern.Size(); i++)
            {
                if ((*node).x == x + pattern[i].x && (*node).y == y + pattern[i].y)
                {
                    if ((*node).piece == nullptr)
                    {
                        if (isCaptureOnly == false)
                        {
                            if (showDot)
                            {
                                (*node).moveDot->Show();
                            }

                            moves.Add(Move(tile->piece, GetTile((*node).x, (*node).y)));
                        }
                    }
                    else if (tile->piece->isWhite != (*node).piece->isWhite && (*node).piece->invinsible == false)
                    {
                        if (tile->piece->canCapture)
                        {
                            if (showDot)
                            {
                                (*node).attackBorder->Show();
                            }

                            moves.Add(Move(tile->piece, GetTile((*node).x, (*node).y), false, GetTile((*node).x, (*node).y)));
                        }
                    }
                }
            }
            for (unsigned int i = 0; i < capturePattern.Size(); i++)
            {
                if ((*node).x == x + capturePattern[i].capture.x && (*node).y == y + (yDirectionInvert * capturePattern[i].capture.y))
                {
                    if ((*node).piece != nullptr)
                    {
                        if (tile->piece->isWhite != (*node).piece->isWhite && (*node).piece->invinsible == false)
                        {
                            if (showDot)
                            {
                                (*node).attackBorder->Show();
                            }

                            // TODO: Add attack pattern here

                            if (tile->x + capturePattern[i].moveTo.x != (*node).x && tile->y + (yDirectionInvert * capturePattern[i].moveTo.y) != (*node).y)
                            {
                                moves.Add(Move(tile->piece, GetTile(tile->x + capturePattern[i].moveTo.x, tile->y + (yDirectionInvert * capturePattern[i].moveTo.y)), false, GetTile((*node).x, (*node).y)));
                            }
                            else
                            {
                                moves.Add(Move(tile->piece, GetTile((*node).x, (*node).y), false, GetTile((*node).x, (*node).y)));
                            }
                        }
                    }
                }
            }
        }

        return moves;
    }

    // The following is Dijkstra’s Algorithm: takes into account movement costs
    Queue<Tile> searchTiles; // TODO: Use a priority queue instead (can use only one container)
    Queue<Tile> nextLayerTiles;

    Tile startTile = *tile;

    searchTiles.Append(startTile);

    yDirectionInvert = 1;

    if (startTile.piece->isWhite == false)
    {
        yDirectionInvert = -1;
    }

    Tile searchTile;
    int frontier = 1;

    while (searchTiles.Empty() == false)
    {
        searchTile = searchTiles.Dequeue();

        for (node = tiles.Begin(); node != NULL; ++node)
        {
            if ((*node).searched == false)
            {
                //The most cursed if statement known to man kind
                if ((tile->piece->isPerpendicularOnly == true && tile->piece->isDiagonalOnly == false && tile->piece->isJester == false &&
                        ((searchTile.x    == (*node).x && searchTile.y - 1 == (*node).y)    ||
                        (searchTile.x + 1 == (*node).x && searchTile.y     == (*node).y)    ||
                        (searchTile.x     == (*node).x && searchTile.y + 1 == (*node).y)    ||
                        (searchTile.x - 1 == (*node).x && searchTile.y     == (*node).y)))  ||
                    (tile->piece->isPerpendicularOnly == false && tile->piece->isDiagonalOnly == false && tile->piece->isJester == false &&
                        ((searchTile.x    == (*node).x && searchTile.y - 1 == (*node).y)    ||
                        (searchTile.x + 1 == (*node).x && searchTile.y - 1 == (*node).y)    ||
                        (searchTile.x + 1 == (*node).x && searchTile.y     == (*node).y)    ||
                        (searchTile.x + 1 == (*node).x && searchTile.y + 1 == (*node).y)    ||
                        (searchTile.x     == (*node).x && searchTile.y + 1 == (*node).y)    ||
                        (searchTile.x - 1 == (*node).x && searchTile.y + 1 == (*node).y)    ||
                        (searchTile.x - 1 == (*node).x && searchTile.y     == (*node).y)    ||
                        (searchTile.x - 1 == (*node).x && searchTile.y - 1 == (*node).y)))  ||
                    (tile->piece->isPerpendicularOnly == false && tile->piece->isDiagonalOnly == true && tile->piece->isJester == false &&
                        ((searchTile.x + 1 == (*node).x && searchTile.y - 1 == (*node).y)   ||
                        (searchTile.x + 1 == (*node).x && searchTile.y + 1 == (*node).y)    ||
                        (searchTile.x - 1 == (*node).x && searchTile.y + 1 == (*node).y)    ||
                        (searchTile.x - 1 == (*node).x && searchTile.y - 1 == (*node).y)))  ||
                    (tile->piece->isJester == true &&
                            (((*node).x + 1 == tile->x && (*node).y == tile->y)     ||
                            ((*node).x - 1 == tile->x && (*node).y == tile->y)      ||
                            ((*node).x + 1 == tile->x && (*node).y + 1 == tile->y)  ||
                            ((*node).x - 1 == tile->x && (*node).y - 1 == tile->y)  ||
                            ((*node).x + 1 == tile->x && (*node).y - 1 == tile->y)  ||
                            ((*node).x - 1 == tile->x && (*node).y + 1 == tile->y)  ||
                            ((*node).x == tile->x && (*node).y + 1 == tile->y)      ||
                            ((*node).x == tile->x && (*node).y - 1 == tile->y))     &&
                        ((searchTile.x + 1 == (*node).x && searchTile.y - 1 == (*node).y)   ||
                        (searchTile.x + 1 == (*node).x && searchTile.y + 1 == (*node).y)    ||
                        (searchTile.x - 1 == (*node).x && searchTile.y + 1 == (*node).y)    ||
                        (searchTile.x - 1 == (*node).x && searchTile.y - 1 == (*node).y)    ||
                        (searchTile.x - 1 == (*node).x && searchTile.y == (*node).y)    ||
                        (searchTile.x + 1 == (*node).x && searchTile.y == (*node).y)    ||
                        (searchTile.x == (*node).x && searchTile.y + 1 == (*node).y)    ||
                        (searchTile.x == (*node).x && searchTile.y - 1 == (*node).y)))  ||
                    (tile->piece->isJester == true &&
                            !(((*node).x + 1 == tile->x && (*node).y == tile->y)    ||
                            ((*node).x - 1 == tile->x && (*node).y == tile->y)      ||
                            ((*node).x + 1 == tile->x && (*node).y + 1 == tile->y)  ||
                            ((*node).x - 1 == tile->x && (*node).y - 1 == tile->y)  ||
                            ((*node).x + 1 == tile->x && (*node).y - 1 == tile->y)  ||
                            ((*node).x - 1 == tile->x && (*node).y + 1 == tile->y)  ||
                            ((*node).x == tile->x && (*node).y + 1 == tile->y)      ||
                            ((*node).x == tile->x && (*node).y - 1 == tile->y))     &&
                        ((searchTile.x + 2 == (*node).x && searchTile.y - 2 == (*node).y)   ||
                        (searchTile.x + 2 == (*node).x && searchTile.y + 2 == (*node).y)    ||
                        (searchTile.x - 2 == (*node).x && searchTile.y + 2 == (*node).y)    ||
                        (searchTile.x - 2 == (*node).x && searchTile.y - 2 == (*node).y)    ||
                        (searchTile.x - 2 == (*node).x && searchTile.y == (*node).y)    ||
                        (searchTile.x + 2 == (*node).x && searchTile.y == (*node).y)    ||
                        (searchTile.x == (*node).x && searchTile.y + 2 == (*node).y)    ||
                        (searchTile.x == (*node).x && searchTile.y - 2 == (*node).y))))
                    {
                    (*node).searched = true;

                    for (unsigned int i = 0; i < pattern.Size(); i++)
                    {
                        if ((*node).x == x + pattern[i].x && (*node).y == y + (yDirectionInvert * pattern[i].y))
                        {
                            if ((*node).piece == nullptr)
                            {
                                if (isCaptureOnly == false)
                                {
                                    if (showDot)
                                    {
                                        (*node).moveDot->Show();
                                    }
                                    if ((*node).weight == 0)
                                    {
                                        nextLayerTiles.Append((*node));
                                    }

                                    Tile* attackTile1 = nullptr;
                                    Tile* attackTile2 = nullptr;
                                    Tile* tileGotten = nullptr;

                                    if (tile->piece->isHydra == true)
                                    {
                                        tileGotten = GetTile((*node).x, (*node).y + 1);
                                        if(tileGotten != nullptr && tileGotten->piece == tile->piece)
                                        {
                                            attackTile1 = GetTile((*node).x - 1, (*node).y);
                                            attackTile2 = GetTile((*node).x + 1, (*node).y);
                                        }

                                        tileGotten = GetTile((*node).x, (*node).y - 1);
                                        if(tileGotten != nullptr && tileGotten->piece == tile->piece)
                                        {
                                            attackTile1 = GetTile((*node).x - 1, (*node).y);
                                            attackTile2 = GetTile((*node).x + 1, (*node).y);
                                        }

                                        tileGotten = GetTile((*node).x - 1, (*node).y - 1);
                                        if(tileGotten != nullptr && tileGotten->piece == tile->piece)
                                        {
                                            attackTile1 = GetTile((*node).x - 1, (*node).y);
                                            attackTile2 = GetTile((*node).x, (*node).y - 1);
                                        }

                                        tileGotten = GetTile((*node).x + 1, (*node).y - 1);
                                        if(tileGotten != nullptr && tileGotten->piece == tile->piece)
                                        {
                                            attackTile1 = GetTile((*node).x, (*node).y - 1);
                                            attackTile2 = GetTile((*node).x + 1, (*node).y);
                                        }

                                        tileGotten = GetTile((*node).x + 1, (*node).y);
                                        if(tileGotten != nullptr && tileGotten->piece == tile->piece)
                                        {
                                            attackTile1 = GetTile((*node).x, (*node).y - 1);
                                            attackTile2 = GetTile((*node).x, (*node).y + 1);
                                        }

                                        tileGotten = GetTile((*node).x - 1, (*node).y);
                                        if(tileGotten != nullptr && tileGotten->piece == tile->piece)
                                        {
                                            attackTile1 = GetTile((*node).x, (*node).y + 1);
                                            attackTile2 = GetTile((*node).x, (*node).y - 1);
                                        }

                                        tileGotten = GetTile((*node).x - 1, (*node).y + 1);
                                        if(tileGotten != nullptr && tileGotten->piece == tile->piece)
                                        {
                                            attackTile1 = GetTile((*node).x, (*node).y + 1);
                                            attackTile2 = GetTile((*node).x - 1, (*node).y);
                                        }

                                        tileGotten = GetTile((*node).x + 1, (*node).y + 1);
                                        if(tileGotten != nullptr && tileGotten->piece == tile->piece)
                                        {
                                            attackTile1 = GetTile((*node).x + 1, (*node).y);
                                            attackTile2 = GetTile((*node).x, (*node).y + 1);
                                        }

                                        if (attackTile1 != nullptr && attackTile1->piece == nullptr)
                                        {
                                            attackTile1 = nullptr;
                                        }
                                        else if (attackTile1 != nullptr && attackTile1->piece->isWhite == tile->piece->isWhite)
                                        {
                                            attackTile1 = nullptr;
                                        }

                                        if (attackTile2 != nullptr && attackTile2->piece == nullptr)
                                        {
                                            attackTile2 = nullptr;
                                        }
                                        else if(attackTile2 != nullptr && attackTile2->piece->isWhite == tile->piece->isWhite)
                                        {
                                            attackTile2 = nullptr;
                                        }

                                        //attackTile2 won't be checked if attackTile1 is nullptr
                                        if (attackTile1 == nullptr && attackTile2 != nullptr)
                                        {
                                            attackTile1 = attackTile2;
                                            attackTile2 = nullptr;
                                        }
                                    }

                                    moves.Add(Move(tile->piece, GetTile((*node).x, (*node).y), false, attackTile1, attackTile2));
                                }
                            }
                            else if (tile->piece->isWhite != (*node).piece->isWhite && (*node).piece->invinsible == false)
                            {
                                if (tile->piece->canCapture)
                                {
                                    if (showDot)
                                    {
                                        (*node).attackBorder->Show();
                                    }

                                    Tile* attackTile1 = GetTile((*node).x, (*node).y);
                                    Tile* attackTile2 = nullptr;
                                    Tile* attackTile3 = nullptr;
                                    Tile* tileGotten = nullptr;

                                    if (tile->piece->isHydra == true)
                                    {

                                        tileGotten = GetTile((*node).x, (*node).y + 1);
                                        if(tileGotten != nullptr && tileGotten->piece == tile->piece)
                                        {
                                            attackTile2 = GetTile((*node).x - 1, (*node).y);
                                            attackTile3 = GetTile((*node).x + 1, (*node).y);
                                        }

                                        tileGotten = GetTile((*node).x, (*node).y - 1);
                                        if(tileGotten != nullptr && tileGotten->piece == tile->piece)
                                        {
                                            attackTile2 = GetTile((*node).x - 1, (*node).y);
                                            attackTile3 = GetTile((*node).x + 1, (*node).y);
                                        }

                                        tileGotten = GetTile((*node).x - 1, (*node).y - 1);
                                        if(tileGotten != nullptr && tileGotten->piece == tile->piece)
                                        {
                                            attackTile2 = GetTile((*node).x - 1, (*node).y);
                                            attackTile3 = GetTile((*node).x, (*node).y - 1);
                                        }

                                        tileGotten = GetTile((*node).x + 1, (*node).y - 1);
                                        if(tileGotten != nullptr && tileGotten->piece == tile->piece)
                                        {
                                            attackTile2 = GetTile((*node).x, (*node).y - 1);
                                            attackTile3 = GetTile((*node).x + 1, (*node).y);
                                        }

                                        tileGotten = GetTile((*node).x + 1, (*node).y);
                                        if(tileGotten != nullptr && tileGotten->piece == tile->piece)
                                        {
                                            attackTile2 = GetTile((*node).x, (*node).y - 1);
                                            attackTile3 = GetTile((*node).x, (*node).y + 1);
                                        }

                                        tileGotten = GetTile((*node).x - 1, (*node).y);
                                        if(tileGotten != nullptr && tileGotten->piece == tile->piece)
                                        {
                                            attackTile2 = GetTile((*node).x, (*node).y + 1);
                                            attackTile3 = GetTile((*node).x, (*node).y - 1);
                                        }

                                        tileGotten = GetTile((*node).x - 1, (*node).y + 1);
                                        if(tileGotten != nullptr && tileGotten->piece == tile->piece)
                                        {
                                            attackTile2 = GetTile((*node).x, (*node).y + 1);
                                            attackTile3 = GetTile((*node).x - 1, (*node).y);
                                        }

                                        tileGotten = GetTile((*node).x + 1, (*node).y + 1);
                                        if(tileGotten != nullptr && tileGotten->piece == tile->piece)
                                        {
                                            attackTile2 = GetTile((*node).x + 1, (*node).y);
                                            attackTile3 = GetTile((*node).x, (*node).y + 1);
                                        }


                                        if (attackTile2 != nullptr && attackTile2->piece == nullptr)
                                        {
                                            attackTile2 = nullptr;
                                        }
                                        else if (attackTile2 != nullptr && attackTile2->piece->isWhite == tile->piece->isWhite)
                                        {
                                            attackTile2 = nullptr;
                                        }

                                        if (attackTile3 != nullptr && attackTile3->piece == nullptr)
                                        {
                                            attackTile3 = nullptr;
                                        }
                                        else if(attackTile3 != nullptr && attackTile3->piece->isWhite == tile->piece->isWhite)
                                        {
                                            attackTile3 = nullptr;
                                        }

                                        //attackTile3 won't be checked if attackTile2 is nullptr
                                        if (attackTile2 == nullptr && attackTile3 != nullptr)
                                        {
                                            attackTile2 = attackTile3;
                                            attackTile3 = nullptr;
                                        }
                                    }

                                    moves.Add(Move(tile->piece, GetTile((*node).x, (*node).y), false, attackTile1, attackTile2, attackTile3));
                                }
                            }
                        }
                    }

                    for (unsigned int i = 0; i < capturePattern.Size(); i++)
                    {
                        if ((*node).x == x + capturePattern[i].capture.x && (*node).y == y + (yDirectionInvert * capturePattern[i].capture.y))
                        {
                            if ((*node).piece != nullptr)
                            {
                                if (tile->piece->isWhite != (*node).piece->isWhite && (*node).piece->invinsible == false)
                                {
                                    if (showDot)
                                    {
                                        (*node).attackBorder->Show();
                                    }

                                    if (tile->x + capturePattern[i].moveTo.x != (*node).x && tile->y + (yDirectionInvert * capturePattern[i].moveTo.y) != (*node).y)
                                    {
                                        moves.Add(Move(tile->piece, GetTile(tile->x + capturePattern[i].moveTo.x, tile->y + (yDirectionInvert * capturePattern[i].moveTo.y)), false, GetTile((*node).x, (*node).y)));
                                    }
                                    else
                                    {
                                        moves.Add(Move(tile->piece, GetTile((*node).x, (*node).y), false, GetTile((*node).x, (*node).y)));
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        if (searchTiles.Empty() == true && nextLayerTiles.Empty() == false)
        {
            LinkedList<Tile>::Iterator nodeNext = nextLayerTiles.Begin();

            for (; nodeNext != NULL; ++nodeNext)
            {
                searchTiles.Append((*nodeNext)); // copy over
            }

            nextLayerTiles.Clear();
            frontier++;
        }

        if (tile->piece->range != 0 && frontier > tile->piece->range)
        {
            break;
        }
    }

    // Reset tile state
    for (node = tiles.Begin(); node != NULL; ++node)
    {
        (*node).searched = false;
        (*node).weight = 0;
    }

    return moves;
}

Tile *Board::GetTile(int x, int y)
{
    LinkedList<Tile>::Iterator node = tiles.Begin();

    for (; node != NULL; ++node)
    {
        if ((*node).x == x && (*node).y == y)
        {
            return &(*node);
        }
    }

    return nullptr;
}

Tile* Board::GetBoardTileUnderMouse()
{
    LinkedList<Tile>::Iterator node = tiles.Begin();

    for (; node != NULL; ++node)
    {
        Sprite* sprite = (*node).sprite;

        if (sprite->IsPressed())
        {
            return &(*node);
        }
    }

    return nullptr;
}

void Board::Init()
{
}

void Board::Update()
{
    LinkedList<Tile>::Iterator tile = tiles.Begin();

    for (; tile != NULL; ++tile)
    {
        (*tile).Update();
        Sprite* sprite = (*tile).sprite;

        if (input.Mouse.Pressed)
        {
            if (sprite->IsPressed())
            {
                //Log(String(tiles[i].x) + " " + String(tiles[i].y));
                //highlight->Show();
                *highlight->matrix.x = *(*tile).sprite->matrix.x;
                *highlight->matrix.y = *(*tile).sprite->matrix.y;

                //HideDots();

                /*if ((*tile).piece)
                {
                    UpdateDots(&(*tile));
                }*/
            }
        }
    }

    highlight->Update();
    bg->Update();

    // Update components manually
    for (unsigned int i = 0; i < components.Size(); i++)
    {
        (*components[i])->Update();
    }
}
