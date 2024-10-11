#pragma once

#include <core/containers/queue.h>

class Move;

static float tileScale = 0.4;
static Queue<Move> replay;

enum Scenes
{
    MainMenu = 0,
    Game
};
