#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#include <core/application.h>

extern int Gold;
extern int Rounds;
extern int RestockCost;
extern bool RestockEndTurn;
extern int RandomCardCost;
extern int PlacementsPerTurn;
extern int MovesPerTurn;

class GameSettings
{
public:
    int Gold = 1000;
    int Rounds = 20;
    int RestockCost = 50;
    bool RestockEndTurn = true;
    int RandomCardCost = 100;
    int PlacementsPerTurn = 1;
    int MovesPerTurn = 1;

    //Count of each piece in deck
    int King = 2;
    int Monster = 3;
    int Queen = 2;
    int Prince = 3;
    int Princess = 3;
    int ShieldMan = 6;
    int Stallion = 3;
    int Jester = 3;
    int Fence = 6;
    int Knight = 3;
    int Peasant = 6;
    int Bishop = 3;
    int Hydra = 3;
    int Rogue = 3;
    int Deserter = 3;
    int Cannon = 3;
    int Rook = 3;

    GameSettings();
    GameSettings(int gold, int rounds);
};

#endif // GAMESETTINGS_H
