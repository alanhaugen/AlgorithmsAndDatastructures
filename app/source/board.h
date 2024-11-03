#ifndef BOARD_H
#define BOARD_H

#include <core/x-platform/scene.h>
#include <core/components/sprite.h>
#include <core/components/camera.h>
#include "tile.h"
#include "tree.h"

class Move;

class Board : public IScene
{
public:
    LinkedList<Tile> tiles;
    Sprite* highlight;
    Board();

    void GenerateTiles();
    void HideDots();
    Array<Move> UpdateDots(Tile *tile, bool showDot = true);
    Tile* GetTile(int x, int y);
    Tile* GetBoardTileUnderMouse();

    void Init();
    void Update();
};

#endif
