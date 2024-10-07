#ifndef BOARD_H
#define BOARD_H

#include <core/components/component.h>
#include <core/components/sprite.h>
#include <core/components/camera.h>
#include "tile.h"

class Board : public Component
{
public:
    Sprite* background;
    LinkedList<Tile> tiles;
    Sprite* highlight;
    Board();

    void GenerateTiles();
    void HideDots();
    void UpdateDots(int x, int y, Array<glm::vec2> patterns);
    Tile* GetBoardTileUnderMouse();

    void Update();
};

#endif
