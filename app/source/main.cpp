#include <core/application.h>
#include "mainmenu.h"
#include "autochess.h"
#include "replayscene.h"
#include "replaynew.h"

bool isTwoPlayer;
bool isFirstPlaythrough;
LinkedList<Move> replay;
LinkedList<ReplayNew> replays;

int main(int argc, char **argv)
{
    Application application(argc, argv);
    application.AddScene(new Mainmenu());
    application.AddScene(new Autochess());
    application.AddScene(new ReplayScene());

    isFirstPlaythrough = true;
    return application.Exec();
}
