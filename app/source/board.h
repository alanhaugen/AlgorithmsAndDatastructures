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
    Sprite* bg;
    Board();

    void GenerateTiles();
    void HideDots();
    Array<Move> UpdateDots(Tile *tile, bool showDot = true, bool isCaptureOnly = false);
    Tile* GetTile(int x, int y);
    Tile* GetBoardTileUnderMouse();

    Array<Move> JumpingMoves(Tile* tile, bool showDot, bool isCaptureOnly);
    Array<Move> DijkstraMoves(Tile* tile, bool showDot, bool isCaptureOnly);

    void Init();
    void Update();
};

#endif
