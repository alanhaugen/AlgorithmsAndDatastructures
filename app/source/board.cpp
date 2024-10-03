#include <core/application.h>
#include "board.h"
#include "main.h"

Board::Board()
{
    background = new Sprite("data/BackgroundImage.png", 0, 0, 0.5, 0.5);

    GenerateTiles();
    HideDots();
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

            *sprite->matrix.x = x * (sprite->width  * sprite->scaleX) + offsetX;
            *sprite->matrix.y = y * (sprite->height * sprite->scaleY) + offsetY;

            tile.sprite = sprite;
            tiles.Add(tile);

            isWhiteTile = !isWhiteTile;
        }

        isWhiteTile = !isWhiteTile;
    }
}

void Board::HideDots()
{
    for (unsigned int i = 0; i < tiles.Size(); i++)
    {
        tiles[i].moveDot->Hide();
    }
}

void Board::Update()
{
    if (input.Pressed(input.Key.BACKSPACE))
    {
        Application::Quit();
    }

    background->Update();

    for (unsigned int i = 0; i < tiles.Size(); i++)
    {
        tiles[i].Update();

        Sprite* sprite = tiles[i].sprite;

        if (input.Mouse.Pressed)
        {
            if ((input.Mouse.x > *sprite->matrix.x && input.Mouse.y > *sprite->matrix.y) &&
                    (input.Mouse.x < *sprite->matrix.x + (sprite->width * sprite->scaleX) && input.Mouse.y < *sprite->matrix.y + (sprite->height * sprite->scaleY)))
            {
                Log(String(tiles[i].x) + " " + String(tiles[i].y));
            }
        }
    }
}

void Board::UpdateAfterPhysics()
{
}
