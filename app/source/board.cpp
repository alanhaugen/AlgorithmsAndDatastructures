#include "board.h"
#include "main.h"

Board::Board()
{
    background = new Sprite("data/BackgroundImage.png", 0, 0, 0.5, 0.5);

    GenerateTiles();
    HideDots();
    highlight = new Sprite("data/TileBorder.png", 0, 0, tileScale, tileScale);
    highlight->Hide();
}

void Board::GenerateTiles()
{
    bool isWhiteTile = true;

    float scale = tileScale;

    Sprite* tile;
    tile = new Sprite("data/WhiteTile.png", 0, 0, scale, scale);

    float offsetX = (renderer->windowWidth / 2) - (tile->width * tile->scaleX  * 5);
    float offsetY = (renderer->windowHeight / 2) - (tile->height * tile->scaleY * 5);

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

    for (; tile != tiles.End(); ++tile)
    {
        (*tile).moveDot->Hide();
        (*tile).attackBorder->Hide();
    }
}

Array<Move> Board::UpdateDots(Tile* tile)
{
    int x = tile->x;
    int y = tile->y;

    Array<glm::vec2> pattern = tile->piece->movePattern;

    LinkedList<Tile>::Iterator node = tiles.Begin();

    Array<Move> moves;

    if (tile->piece->isJumping)
    {
        for (node = tiles.Begin(); node != tiles.End(); ++node)
        {
            for (unsigned int i = 0; i < pattern.Size(); i++)
            {
                if ((*node).x == x + pattern[i].x && (*node).y == y + pattern[i].y)
                {
                    if ((*node).piece == nullptr)
                    {
                        (*node).moveDot->Show();
                        moves.Add(Move(tile->piece, glm::vec2((*node).x, (*node).y)));
                    }
                    else if (tile->piece->isWhite != (*node).piece->isWhite)
                    {
                        (*node).attackBorder->Show();
                        moves.Add(Move(tile->piece, glm::vec2((*node).x, (*node).y), true));
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

    int yDirectionInvert = 1;

    if (startTile.piece->isWhite == false)
    {
        yDirectionInvert = -1;
    }

    Tile searchTile;

    while (searchTiles.Empty() == false)
    {
        searchTile = searchTiles.Dequeue();

        for (node = tiles.Begin(); node != tiles.End(); ++node)
        {
            if ((*node).searched == false)
            {
                if (    (searchTile.x     == (*node).x && searchTile.y - 1 == (*node).y) ||
                        (searchTile.x + 1 == (*node).x && searchTile.y - 1 == (*node).y) ||
                        (searchTile.x + 1 == (*node).x && searchTile.y     == (*node).y) ||
                        (searchTile.x + 1 == (*node).x && searchTile.y + 1 == (*node).y) ||
                        (searchTile.x     == (*node).x && searchTile.y + 1 == (*node).y) ||
                        (searchTile.x - 1 == (*node).x && searchTile.y + 1 == (*node).y) ||
                        (searchTile.x - 1 == (*node).x && searchTile.y     == (*node).y) ||
                        (searchTile.x - 1 == (*node).x && searchTile.y - 1 == (*node).y))
                {
                    (*node).searched = true;

                    for (unsigned int i = 0; i < pattern.Size(); i++)
                    {
                        if ((*node).x == x + pattern[i].x && (*node).y == y + (yDirectionInvert * pattern[i].y))
                        {
                            if ((*node).piece == nullptr)
                            {
                                (*node).moveDot->Show();
                                nextLayerTiles.Append((*node));
                                moves.Add(Move(tile->piece, glm::vec2((*node).x, (*node).y)));
                            }
                            else if (tile->piece->isWhite != (*node).piece->isWhite)
                            {
                                (*node).attackBorder->Show();
                                moves.Add(Move(tile->piece, glm::vec2((*node).x, (*node).y), true));
                            }
                        }
                    }
                }
            }
        }

        if (searchTiles.Empty() == true && nextLayerTiles.Empty() == false)
        {
            LinkedList<Tile>::Iterator nodeNext = nextLayerTiles.Begin();

            for (; nodeNext != nextLayerTiles.End(); ++nodeNext)
            {
                searchTiles.Append((*nodeNext)); // copy over
            }

            nextLayerTiles.Clear();
        }
    }

    // Reset tile state
    for (node = tiles.Begin(); node != tiles.End(); ++node)
    {
        (*node).searched = false;
    }

    return moves;
}

Tile *Board::GetTile(int x, int y)
{
    LinkedList<Tile>::Iterator node = tiles.Begin();

    for (; node != tiles.End(); ++node)
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

    for (; node != tiles.End(); ++node)
    {
        Sprite* sprite = (*node).sprite;

        if (sprite->IsPressed())
        {
            return &(*node);
        }
    }

    return nullptr;
}


void Board::Update()
{
    background->Update();

    LinkedList<Tile>::Iterator tile = tiles.Begin();

    for (; tile != tiles.End(); ++tile)
    {
        (*tile).Update();
        Sprite* sprite = (*tile).sprite;

        if (input.Mouse.Pressed)
        {
            if (sprite->IsPressed())
            {
                //Log(String(tiles[i].x) + " " + String(tiles[i].y));
                highlight->Show();
                *highlight->matrix.x = *(*tile).sprite->matrix.x;
                *highlight->matrix.y = *(*tile).sprite->matrix.y;

                HideDots();

                if ((*tile).piece)
                {
                    UpdateDots(&(*tile));
                }
            }
        }
    }

    highlight->Update();
}
