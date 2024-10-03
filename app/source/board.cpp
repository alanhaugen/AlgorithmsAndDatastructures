#include <core/application.h>
#include "board.h"

Board::Board()
{
    cam = new Camera();

    background = new Sprite("data/BackgroundImage.png", 0, 0, 0.5, 0.5);

    bool isWhiteTile = true;

    float scale = 0.25;

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

            *sprite->matrix.x = x * (sprite->width  * sprite->scaleX) + offsetX;
            *sprite->matrix.y = y * (sprite->height * sprite->scaleY) + offsetY;

            tile.sprite = sprite;
            tiles.Add(tile);

            isWhiteTile = !isWhiteTile;
        }

        isWhiteTile = !isWhiteTile;
    }

    cursor = new Sprite("data/BlackCursor.png", 0, 0, 1.0, 1.0);
}

void Board::Update()
{
    if (input.Pressed(input.Key.BACKSPACE))
    {
        Application::Quit();
    }

    background->Update();

    //Physics::IPhysics::Ray cameraRay = cam->ScreenPointToRay(input.Mouse.x, input.Mouse.y);

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

        /*if (physics->Intersect(cameraRay, tiles[i].sprite->collisionBox))
        {
            activePiece = piece;
            activePiece->Uniform("colour", glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
            dragging = true;
            break;
        }*/
    }

    *cursor->matrix.x = input.Mouse.x;
    *cursor->matrix.y = input.Mouse.y;
    cursor->Update();
}

void Board::UpdateAfterPhysics()
{
}
