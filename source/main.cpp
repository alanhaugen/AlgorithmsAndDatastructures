#include <core/application.h>
#include "mainmenu.h"
#include "autochess.h"
#include "replayscene.h"
#include "replaynew.h"
#include "gamesettings.h"

bool isTwoPlayer = false;
bool vsAI = false;
bool isFirstPlaythrough = true;
LinkedList<Move> replay;
LinkedList<ReplayNew> replays;
LinkedList<GameSettings*> Presets;
int MovesTotal = 20;
bool option = false;

int Gold = 1000;
int Rounds = 20;
int RestockCost = 50;
bool RestockEndTurn = true;
int RandomCardCost = 100;
int PlacementsPerTurn = 1;
int MovesPerTurn = 1;

int main(int argc, char **argv)
{
    Application application(argc, argv, "Fight of Kings", 1366, 800);
    application.AddScene(new Mainmenu());
    application.AddScene(new Autochess());
    application.AddScene(new ReplayScene());

    return application.Exec();
}
