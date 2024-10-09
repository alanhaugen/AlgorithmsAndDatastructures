#ifndef BOARD_H
#define BOARD_H

#include <core/components/component.h>
#include <core/components/sprite.h>
#include <core/components/camera.h>
#include "tile.h"
#include "tree.h"

class Move;

class Board : public Component
{
public:
    Sprite* background;
    LinkedList<Tile> tiles;
    Sprite* highlight;
    Board();

    void GenerateTiles();
    void HideDots();
    Array<Move> UpdateDots(Tile *tile);
    Tile* GetTile(int x, int y);
    Tile* GetBoardTileUnderMouse();

    void Update();
};

#endif
