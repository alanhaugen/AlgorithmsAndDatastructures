#include <core/application.h>
#include "mainmenu.h"
#include "autochess.h"
#include "replay.h"

bool isTwoPlayer;
LinkedList<Move> replay;
LinkedList<Replay> replays;

int main(int argc, char **argv)
{
    Application application(argc, argv);
    application.AddScene(new Mainmenu());
    application.AddScene(new Autochess());

    return application.Exec();
}
